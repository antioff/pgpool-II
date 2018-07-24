/*
 * $Header$
 *
 * Handles watchdog connection, and protocol communication with pgpool-II
 *
 * pgpool: a language independent connection pool server for PostgreSQL 
 * written by Tatsuo Ishii
 *
 * Copyright (c) 2003-2012	PgPool Global Development Group
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of the
 * author not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission. The author makes no representations about the
 * suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <netdb.h>
#include "pool.h"
#include "pool_config.h"
#include "watchdog.h"
#include "wd_ext.h"

#include "libpq-fe.h"

int is_wd_lifecheck_ready(void);
int wd_lifecheck(void);
int wd_ping_pgpool(WdInfo * pgpool);
static void * ping_pgpool(void * arg);
static PGconn * create_conn(char * hostname, int port);
static int pgpool_down(WdInfo * pool);

int
is_wd_lifecheck_ready(void)
{
	PGconn * conn = NULL;
	PGresult * res = (PGresult *)NULL;
	int status;
	int rtn = WD_OK;
	WdInfo * p = WD_List;
	while (p->status != WD_END)
	{
		conn = create_conn(p->hostname, p->pgpool_port);
		if (conn != NULL)
		{
			res = PQexec(conn, pool_config->wd_lifecheck_query );

			status = PQresultStatus(res);
			if (res != NULL)
			{
				PQclear(res);
			}
			if ((status == PGRES_NONFATAL_ERROR )|| 
				(status == PGRES_FATAL_ERROR ))
			{
				rtn = WD_NG;
			}
			PQfinish(conn);
		}
		else
		{
			rtn = WD_NG;
		}
		p ++;
	}

	if (rtn == WD_OK)
	{
		pool_log("watchdog: lifecheck started");
	}
	return rtn;
}

int
wd_lifecheck(void)
{
	WdInfo * p = WD_List;
	pthread_attr_t attr;
	int rc;
	int i,cnt;
	struct timeval tv;
	pthread_t thread[MAX_WATCHDOG_NUM];
	WdPgpoolThreadArg thread_arg[MAX_WATCHDOG_NUM];


	/* set startup time */
	gettimeofday(&tv, NULL);

	/* check upper connection */
	if ((pool_config->trusted_servers != NULL) &&
		(strlen(pool_config->trusted_servers ) > 0) &&
		(wd_is_upper_ok(pool_config->trusted_servers) != WD_OK))
	{
		pool_error("wd_lifecheck: failed to connect to any trusted servers");

		/* This server connection may be downed */
		if (p->status == WD_MASTER)
		{
			wd_IP_down();
		}
		wd_set_myself(&tv, WD_DOWN);
		wd_notice_server_down();
		return WD_NG;
	}

	/* skip lifecheck during recovery execution */
	if (*InRecovery != RECOVERY_INIT)
	{
		return WD_OK;
	}

	/* thread init */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	/* send packet to all watchdogs */
	cnt = 0;
	while (p->status != WD_END)
	{
		thread_arg[cnt].conn = create_conn(p->hostname, p->pgpool_port);
		rc = pthread_create(&thread[cnt], &attr, ping_pgpool, (void*)&thread_arg[cnt]);
		p ++;
		cnt ++;
		if (cnt >= MAX_WATCHDOG_NUM)
		{
			pool_error("wd_lifecheck: pgpool num is out of range(%d)",cnt);
			break;
		}
	}
	pthread_attr_destroy(&attr);
	p = WD_List;
	for (i = 0; i < cnt; )
	{
		int result;

		pool_debug("wd_lifecheck: checking pgpool %d (%s:%d)", i, p->hostname, p->pgpool_port);	

		rc = pthread_join(thread[i], (void **)&result);
		if ((rc != 0) && (errno == EINTR))
		{
			usleep(100);
			continue;
		}
		if (result == WD_OK)
		{
			pool_debug("wd_lifecheck: OK, status: %d", p->status);	

			p->life = pool_config->wd_life_point;
			if ((i == 0) &&
				(WD_List->status == WD_DOWN))
			{
				wd_set_myself(&tv, WD_NORMAL);
				wd_startup();
				/* check existence of master pgpool */
				if (wd_is_alive_master() == NULL )
				{
					pool_debug("wd_is_alive_master: there isn't any alive master");

					/* escalate to delegate_IP holder */
					wd_escalation();
				}
			}
		}
		else
		{
			pool_debug("wd_lifecheck: NG, status: %d life:%d", p->status, p->life);	

			if (p->life > 0)
			{
				p->life --;
			}
			if (p->life <= 0)
			{
				pool_log("wd_lifecheck: lifecheck failed %d times. pgpool seems not to be working",
				         pool_config->wd_life_point);

				if ((i == 0) &&
					(WD_List->status != WD_DOWN))
				{
					wd_set_myself(&tv, WD_DOWN);
					wd_notice_server_down();
				}
				else
				{
					pgpool_down(p);
				}
			}
		}
		pthread_detach(thread[i]);
		i++;
		p++;
	}
	return WD_OK;
}

static void *
ping_pgpool(void * arg)
{
	WdPgpoolThreadArg * thread_arg;
	PGconn * conn;
	uintptr_t rtn = (uintptr_t)WD_NG;
	int status = PGRES_FATAL_ERROR;
	PGresult * res = (PGresult *)NULL;
	thread_arg = (WdPgpoolThreadArg *)arg;
	conn = thread_arg->conn;

	res = PQexec(conn, pool_config->wd_lifecheck_query );

	status = PQresultStatus(res);
	if (res != NULL)
	{
		PQclear(res);
	}
	if ((status != PGRES_NONFATAL_ERROR ) &&
		(status != PGRES_FATAL_ERROR ))
	{
		rtn = WD_OK;
	}
	PQfinish(conn);
	pthread_exit((void *)rtn);
}

static PGconn *
create_conn(char * hostname, int port)
{
	static char conninfo[1024];
	PGconn *conn;

	snprintf(conninfo,sizeof(conninfo),
		"host='%s' port='%d' dbname='template1' user='%s' password='%s' connect_timeout='%d'",
		hostname, 
		port, 
		pool_config->recovery_user,
		pool_config->recovery_password,
		pool_config->wd_interval / 2 + 1);
	conn = PQconnectdb(conninfo);
	if (PQstatus(conn) != CONNECTION_OK)
	{
		PQfinish(conn);
		return NULL;
	}
	return conn;
}

static int
pgpool_down(WdInfo * pool)
{
	int rtn = WD_DOWN;
	if ((WD_List->status == WD_NORMAL) &&
		(pool->status == WD_MASTER))
	{
		pool->status = WD_DOWN;
		if (wd_am_I_oldest() == WD_OK)
		{
			/* stand for master */
			rtn = wd_stand_for_master();
			if (rtn == WD_OK)
			{
				/* win */
				wd_escalation();
			}
		}
	}
	pool->status = WD_DOWN;
	return rtn;
}

int
wd_ping_pgpool(WdInfo * pgpool)
{
	int rtn = WD_NG;
	PGconn * conn;
	int status = PGRES_FATAL_ERROR;
	PGresult * res = (PGresult *)NULL;

	conn = create_conn(pgpool->hostname, pgpool->pgpool_port);
	res = PQexec(conn, pool_config->wd_lifecheck_query );

	status = PQresultStatus(res);
	if (res != NULL)
	{
		PQclear(res);
	}
	if ((status != PGRES_NONFATAL_ERROR ) &&
		(status != PGRES_FATAL_ERROR ))
	{
		rtn = WD_OK;
	}
	PQfinish(conn);

	return rtn;
}
