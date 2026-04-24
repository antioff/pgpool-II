#!/bin/sh
PGPOOL_VER="4.7.1"

git init

wget https://www.pgpool.net/mediawiki/download.php?f=pgpool-II-$PGPOOL_VER.tar.gz  -O pgpool-II-$PGPOOL_VER.tar.gz
gear-update -c -f -t 'tar' pgpool-II-$PGPOOL_VER.tar.gz pgpool-II
rm -f pgpool-II-$PGPOOL_VER.tar.gz

git add pgpool-II
git commit -m "Initial repo"

git checkout -b upstream
git tag v$PGPOOL_VER
git checkout main
git merge -s ours upstream


mkdir .gear
###########
cat > ".gear/rules" << \EOF
specsubst: pgver
copy?: *.conf
copy?: *.init
copy?: *.service
copy?: *.sysconfig
copy?: *.tmpfiles
tar: v@version@:pgpool-II name=pgpool-II-@version@
diff: v@version@:pgpool-II pgpool-II name=pgpool-II-@version@-@release@.patch
EOF
##########

cat > "pgpro_repo.sh" << \EOF
#!/bin/sh
PG_VER=18

LISTNAME="pgpro_${PG_VER}"
if [ ! -f /etc/apt/sources.list.d/$LISTNAME.list ]; then

ALT_ID=`grep VERSION_ID /etc/os-release | cut -d= -f2 | cut -d. -f1`
ARCH=$(rpm -q --qf="%{arch}" rpm)

REPO="https://repo.postgrespro.ru/1c/1c-$PG_VER/altlinux/$ALT_ID"
LISTNAME="pgpro_${PG_VER}"
if [ ! -d /etc/pki/$LISTNAME ]; then
     mkdir -p /etc/pki/$LISTNAME
fi
keyfile=/etc/pki/$LISTNAME/RPM-GPG-KEY-POSTGRESPRO

cat > "$keyfile" << KEY-PGPRO
-----BEGIN PGP PUBLIC KEY BLOCK-----
Version: GnuPG v1

mQENBFWdEjABCAC6QeLt0UJUQlDI2Z+R/y1OyOMU+5Te176I0+/Xpc2v5NsucW2M
kLTdOif0iW+q5h1djL+Pc5yu1fojZCvcihhbURnWECF52BmRnOC9jI0eTHq3fcPZ
IE3gqMJSn5sx2kJZ7n8XE0RbQ/hr51BLI+lzeqR3JAKBIqpVDKRrdP9Y1xVR/7Ne
q4FNR+osm6W4sM9G+TA/YADrWX3/TPXA4AN+2uNCNY0wK7em8V0oSZJVpEzvu5EP
djC6GX08XSvhPNo52o3u3tpFWH7ICw2BEYe672bJTjmi8wFgPW04pw49Jpvw4i1R
RhkpQqQ/b9bSveoNpvN32ElAJSaize76+q/TABEBAAG0KlJvYm90IChTaWduaW5n
IHJlcG9zKSA8ZGJhQHBvc3RncmVzcHJvLnJ1PokBOAQTAQIAIgUCVZ0SMAIbAwYL
CQgHAwIGFQgCCQoLBBYCAwECHgECF4AACgkQf5rlpi0t8LQpKQgAuJkOKNdnCSCt
GbNTwAbk414UPYa2B1M1DD6MfcSd6NnJNBVtRoaSWWISQB6gP+/w1jmD8XZbj/oH
5HAHjOyh9Lb3z1xeMIQnBnfGtcqmU5QrF55Yi0H9G0s+fn9oodfNXqAa/zARpBw6
q3LRSBCjT50/XA5G3AzUr7fIDb68FmEOCQukzs0uWBr5fkrRC21b1DcuhzbBay8X
pnlpB+Ma1PTIFgRdRl/KwYTzO80TWFMCeYfXQRh8StuQxRcVCqnv4F6seHqmbL7A
vOZ7GMymsz/IRHGVk4eVC6/94Y3vkV/0eQ+Yom+NtAFnep6G4OhxIeviZ697eFYF
+j4YsyDD+g==
=Q7MS
-----END PGP PUBLIC KEY BLOCK-----
KEY-PGPRO

apt-get install -y apt-https 
echo "rpm $REPO $ARCH pgpro" > "/etc/apt/sources.list.d/$LISTNAME.list"
echo "rpm $REPO noarch pgpro" >> "/etc/apt/sources.list.d/$LISTNAME.list"
chmod 0644 "/etc/apt/sources.list.d/$LISTNAME.list"
apt-get update 
fi
EOF

############
chmod +x pgpro_repo.sh
############
cat > "update.sh" << \EOF
#!/bin/sh
PGPOOL_VER=`grep Version pgpool-II.spec | grep -oE '[0-9.]+'`
PGPOOL_SRC=`grep AC_INIT pgpool-II/configure.ac | cut -d, -f2 | grep -oE '[0-9.]+'`

if [ "$PGPOOL_VER" != "$PGPOOL_SRC" ];then
git checkout upstream
wget https://www.pgpool.net/mediawiki/download.php?f=pgpool-II-$PGPOOL_VER.tar.gz  -O pgpool-II-$PGPOOL_VER.tar.gz
gear-update -t 'tar' pgpool-II-$PGPOOL_VER.tar.gz pgpool-II
rm -f pgpool-II-$PGPOOL_VER.tar.gz

git add -A
git commit -m "Update upstream"
git tag -f "v$PGPOOL_VER"

git checkout main
gear-store-tags -ac
fi

git merge upstream -m "Merge with upstream PGPOOL $PGPOOL_VER"

git add -A
git commit -m "Update version PGPOOL $PGPOOL_VER"

gear-create-tag -f -n "postgrespro-1c-18-$PGPOOL_VER" -s pgver=postgrespro-1c-18
gear-create-tag -f -n "postgresql17-$PGPOOL_VER" -s pgver=postgresql17

EOF
############
chmod +x update.sh


cat > "github_update.sh" << \EOF
PGPOOL_VER=`grep Version pgpool-II.spec | grep -oE '[0-9.]+'`
git add -A
git commit -m "Update"
gear-create-tag -f -n "postgrespro-1c-18-$PGPOOL_VER" -s pgver=postgrespro-1c-18
gear-create-tag -f -n "postgresql17-$PGPOOL_VER" -s pgver=postgresql17
git push
git push origin --force --tags
EOF
############
chmod +x github_update.sh



cat > "pgpool.init" << \EOF
#!/bin/sh
# /etc/init.d/pgpool
# chkconfig:    2345 90 14
# description:  Starts and stops the pgpool daemon.
# processname: pgpool
# Do not load RH compatibility interface.
WITHOUT_RC_COMPAT=1
# Source function library.
. /etc/init.d/functions

PGUSER=postgres
BINARY="/usr/bin/pgpool"
#OPTIONS="-f /etc/pgpool.conf"
STOP_OPTIONS="-m fast stop"
#PIDFILE=/var/run/pgpool/pgpool.pid
#LOCKFILE=/var/lock/subsys/pgpool
RETVAL=0

CFGS=$(/bin/ls -1 /etc/pgpool.d/*)
CFGS="${CFGS//\/etc\/pgpool.d\//}"

#echo $CFGS

buildenv()
{
                        CONFIG="/etc/pgpool.d/$1"
                        PIDFILE="${CONFIG%.conf}.pid"
                        PIDFILE="/var/run/pgpool/${PIDFILE#/etc/pgpool.d/}"
                        LOCKFILE="${CONFIG/.conf/}"
                        LOCKFILE="/var/lock/subsys/${LOCKFILE#/etc/pgpool.d/}"
}


noargs_start()
{
        for CONFIG in $CFGS ; do
                buildenv $CONFIG


                        if [ -f "$PIDFILE" ]; then
                                failure "$PIDFILE exists. Probably another instance of pgpool is running ?..."
                        else
                            if start_daemon --user "$PGUSER"  --expect-user root --displayname pgpool -- "$BINARY" "-f $CONFIG 2>&1|logger -t pgpool -p local0.info "
#                               action "Starting pgpool:" "su -s /bin/sh -c '/usr/bin/pgpool -n -f $CONFIG  2>&1|logger -t pgpool -p local0.info &' $PGUSER"
                                then
                                    	echo_success
                            else
                                echo_failure
                            fi
                        fi

        done
        RETVAL=$?
    return $RETVAL

}

noargs_stop()
{
                for CONFIG in $CFGS ; do
                                buildenv $CONFIG
                        if [ -f "$PIDFILE" ]; then
                                        stop_daemon --pidfile "$PIDFILE" --expect-user "$PGUSER" --displayname pgpool -- "$BINARY" "$STOP_OPTIONS"
                        fi
                done
}


noargs_reload()
{
        for CONFIG in $CFGS ; do
                buildenv $CONFIG
            if [ -f "$PIDFILE" ]; then
                                if /bin/su -s /bin/sh -c "/bin/kill -HUP $(/bin/cat $PIDFILE)" $PGUSER 2> /dev/null > /dev/null; then
                                echo_success
                                        else
                                echo_failure
                                fi
            fi
        done
}





start()
{
        if [ $# -eq 0 ]; then

                                                        noargs_start            
                else
                        buildenv $1
                        if [ -f "$PIDFILE" ]; then
                                failure "$PIDFILE exists. Probably another instance of pgool is running ?..."
                        else
                                if 
                                        start_daemon --user "$PGUSER"  --expect-user root --displayname pgpool -- "$BINARY" " -f $CONFIG 2>&1|logger -t pgpool -p local0.info"; 
                                then
                                        echo_success
                                else
                                        echo_failure
                                fi
                        fi
        fi

        RETVAL=$?
        return $RETVAL
}


stop()
{
        if [ $# -eq 0 ]; then

                                        noargs_stop
                                                else
        buildenv $1
        stop_daemon --pidfile "$PIDFILE" --expect-user "$PGUSER" --displayname pgpool -- "$BINARY" "$STOP_OPTIONS"
        fi
        RETVAL=$?
        return $RETVAL
}

restart()
{
   stop $1
   start $1
}

reload()
{
        if [ $# -eq 0 ]; then

        noargs_reload

                                        else
                                        buildenv $1
                                                if /bin/su -s /bin/sh -c "/bin/kill -HUP $(/bin/cat $PIDFILE)" $PGUSER 2> /dev/null > /dev/null; then
                                                        echo_success
                                                                else
                                                        echo_failure
                                                fi
        fi
        echo
}

case "$1" in
   start)
        shift
        start "$@"
   ;;
   stop)
        shift
        stop "$@"
   ;;
   restart)
        shift
        restart "$@"
    ;;
   reload)
    shift
        reload "$@"
   ;;
   condrestart)
   if [ -e "$LOCKFILE" ]; then
                   restart
   fi
   ;;
   condreload)
   if [ -e "$LOCKFILE" ]; then
                   reload
   fi
   ;;
   *)
    msg_usage "${0##*/} {start|stop|restart|reload|condrestart|condreload}"
    RETVAL=1
esac

exit $RETVAL
EOF
############
chmod +x pgpool.init


cat > "pgpool.service" << \EOF
[Unit]
Description=PGPool-II
Documentation=man:pgpool(8)
After=network.target

[Service]
User=postgres
Group=postgres
EnvironmentFile=-/etc/sysconfig/pgpool
ExecStart=/usr/bin/pgpool -n -f /etc/pgpool/pgpool.conf $OPTS
ExecStop=/usr/bin/pgpool -f /etc/pgpool/pgpool.conf $STOP_OPTS stop
ExecReload=/usr/bin/pgpool -f /etc/pgpool/pgpool.conf reload

[Install]
WantedBy=multi-user.target

EOF
############

cat > "pgpool.sysconfig" << \EOF
# Options for pgpool
# -d: debug mode. lots of debug information will be printed
#OPTS=" -d"

STOP_OPTS=" -m fast"

EOF
############

cat > "pgpool.tmpfiles" << \EOF
d /var/run/pgpool 0775 root postgres -

EOF
############

cat > "pgpool-II.spec" << \EOF
%define PG_VER @pgver@
%define PROG_NAME pgpool-II
%define SNAME pgpool
%define PG_NUM %(expr `echo %PG_VER | tail -c 3` + 0)
%define PG_PRO %(echo %PG_VER | grep -q "pro" && echo 1 || echo 0)
%define PG_PREFIX  %([ %PG_PRO -eq 1 ] && echo "/opt/pgpro/1c-%PG_NUM" || echo "%_usr")
%define ALT_ID %(expr `grep VERSION_ID /etc/os-release | cut -d= -f2 | cut -d. -f1` + 0)

%if %PG_NUM > 17
ExcludeArch: %ix86
%endif

%if %PG_PRO
%set_verify_elf_method rpath=relaxed
%endif


Packager:       antioff <nobody@altlinux.org>
Name: %PG_VER-%PROG_NAME
Version: 4.7.1
Release: alt3
Summary: Pgpool is a connection pooling/replication server for PostgreSQL
License: BSD
Group: Databases
# Source git://git.postgresql.org/git/pgpool2.git
Url: http://www.pgpool.net
Source: %PROG_NAME-%version.tar
Source1: pgpool.service
Source2: pgpool.tmpfiles
Source3: pgpool.init
Source4: pgpool.sysconfig
Patch0:  %PROG_NAME-%version-%release.patch

BuildRequires: OpenSP
BuildRequires: docbook-style-dsssl
BuildRequires: docbook-style-dsssl-utils
BuildRequires: docbook-style-xsl
BuildRequires: perl-parent
BuildRequires: xsltproc
BuildRequires: flex
BuildRequires: libpam-devel
BuildRequires: libmemcached-devel
BuildRequires: libssl-devel
BuildRequires: %([ %ALT_ID -lt 11 ] && echo "libecpg6-devel" || echo "libecpg6-%PG_NUM-devel")
BuildRequires: %([ %PG_PRO -eq 1 ] && echo "%PG_VER-devel" || echo "%PG_VER-server-devel")
BuildRequires: %([ %ALT_ID -lt 11 ] && echo "libpq-devel" || echo "libpq5-%PG_NUM-devel")

Provides: pgpool2 = %EVR
Conflicts: pgpool2 < %EVR
Requires:  %([ %PG_PRO -eq 1 ] && echo "%PG_VER" || echo "%PG_VER-server")

%description
pgpool-II is a inherited project of pgpool (to classify from
pgpool-II, it is sometimes called as pgpool-I). For those of
you not familiar with pgpool-I, it is a multi-functional
middle ware for PostgreSQL that features connection pooling,
replication and load balancing functions. pgpool-I allows a
user to connect at most two PostgreSQL servers for higher
availability or for higher search performance compared to a
single PostgreSQL server.

Postgresql extensions libraries and sql files for pgpool-II.

%prep
%setup -n %PROG_NAME-%version
%autopatch -p1

%build

export CC=%__cc
export CXX=%__cxx

%autoreconf
%configure \
    --disable-static \
    --with-pam \
    --with-openssl \
    --disable-rpath \
    --with-memcached=%_includedir/libmemcached \
    --with-pgsql=%PG_PREFIX \
    --with-pgsql-includedir=`%PG_PREFIX/bin/pg_config --includedir` \
    --with-pgsql-libdir=`%PG_PREFIX/bin/pg_config --libdir` \
    --sysconfdir=%_sysconfdir/%SNAME

%make_build -j1
%make_build PG_CONFIG=%PG_PREFIX/bin/pg_config -C src/sql/pgpool-recovery
%make_build PG_CONFIG=%PG_PREFIX/bin/pg_config -C src/sql/pgpool-regclass
%make_build PG_CONFIG=%PG_PREFIX/bin/pg_config -C src/sql/pgpool_adm
%make_build -C doc all

%install
%make DESTDIR=%buildroot install
%make PG_CONFIG=%PG_PREFIX/bin/pg_config DESTDIR=%buildroot install -C src/sql/pgpool-recovery
%make PG_CONFIG=%PG_PREFIX/bin/pg_config DESTDIR=%buildroot install -C src/sql/pgpool-regclass
%make PG_CONFIG=%PG_PREFIX/bin/pg_config DESTDIR=%buildroot install -C src/sql/pgpool_adm

mkdir -p %buildroot{{%_logdir,%_datadir}/%SNAME,%_unitdir,%_initdir,%_tmpfilesdir,%_man1dir,%_man8dir}

install -p -m644 %SOURCE1 %buildroot%_unitdir/%SNAME.service
install -p -m644 %SOURCE2 %buildroot%_tmpfilesdir/%SNAME.conf
install -p -m755 %SOURCE3 %buildroot%_initdir/%SNAME
install -p -m644 -D %SOURCE4 %buildroot%_sysconfdir/sysconfig/%SNAME

mv %buildroot%_sysconfdir/%SNAME/pcp.conf.sample %buildroot%_sysconfdir/%SNAME/pcp.conf
mv %buildroot%_sysconfdir/%SNAME/pgpool.conf.sample %buildroot%_sysconfdir/%SNAME/pgpool.conf
mv %buildroot%_sysconfdir/%SNAME/pool_hba.conf.sample  %buildroot%_sysconfdir/%SNAME/pool_hba.conf
mv %buildroot%_sysconfdir/%SNAME/failover.sh.sample %buildroot%_sysconfdir/%SNAME/failover.sh
mv %buildroot%_sysconfdir/%SNAME/follow_primary.sh.sample %buildroot%_sysconfdir/%SNAME/follow_primary.sh
mv %buildroot%_sysconfdir/%SNAME/pgpool_remote_start.sample %buildroot%_sysconfdir/%SNAME/pgpool_remote_start
mv %buildroot%_sysconfdir/%SNAME/recovery_1st_stage.sample %buildroot%_sysconfdir/%SNAME/recovery_1st_stage

cp doc/src/sgml/man1/* %buildroot%_man1dir/
cp doc/src/sgml/man8/* %buildroot%_man8dir/

rm -f %buildroot%_libdir/*.{a,la}

%post
# Migrate configs from pgpool < 4.2.1
if [ $1 -eq 2 ]; then
    [ ! -f %_sysconfdir/pcp.conf ] || mv -f %_sysconfdir/pcp.conf %_sysconfdir/%SNAME/pcp.conf
    [ ! -f %_sysconfdir/pgpool.conf ] || mv -f %_sysconfdir/pgpool.conf %_sysconfdir/%SNAME/pgpool.conf
    [ ! -f %_sysconfdir/pool_hba.conf ] || mv -f %_sysconfdir/pool_hba.conf %_sysconfdir/%SNAME/pool_hba.conf
    chown root:postgres %_sysconfdir/%SNAME/*
    chmod 640 %_sysconfdir/%SNAME/*
fi
%post_service %SNAME

%preun
%preun_service %SNAME

%files
%doc NEWS COPYING src/sample doc/src/sgml/html
%dir %attr(750,root,postgres) %_sysconfdir/%SNAME
%config(noreplace) %attr(640,root,postgres) %_sysconfdir/%SNAME/*
%config(noreplace) %_sysconfdir/sysconfig/%SNAME

%_initdir/*

%_unitdir/*
%_tmpfilesdir/*

%_bindir/*
%_datadir/*
%_libdir/*

%if %PG_PRO
/opt/*
%endif

%_var/*

%attr(1775,root,postgres) %dir %_logdir/%SNAME

%changelog
* Wed Apr 22 2026 Anton Zamilov <noname@altlinux.org> 4.7.1-alt3
- add postgrespro tag

* Tue Mar 17 2026 Alexei Takaseev <taf@altlinux.org> 4.7.1-alt2
- Use LLVM if it used in PostgreSQL

* Fri Feb 27 2026 Alexei Takaseev <taf@altlinux.org> 4.7.1-alt1
- 4.7.1

EOF
############

git add -A
git commit -m "Add spec and pgpool service files"


cd pgpool-II

git checkout main

sed -i 's|#define DEFAULT_WD_IPC_SOCKET_DIR "/tmp"|#define DEFAULT_WD_IPC_SOCKET_DIR "/var/run/pgpool"|' src/include/pool.h
sed -i 's|#define DEFAULT_SOCKET_DIR "/tmp"|#define DEFAULT_SOCKET_DIR "/var/run/pgpool"|' src/include/pool.h
sed -i 's|#define DEFAULT_LOGDIR "/tmp"|#define DEFAULT_LOGDIR "/var/log/pgpool"|' src/include/pool.h
sed -i "s|#unix_socket_directories = '/tmp'|unix_socket_directories = '/var/run/pgpool'|" src/sample/pgpool.conf.sample
sed -i "s|#pcp_socket_dir = '/tmp'|pcp_socket_dir = '/var/run/pgpool'|" src/sample/pgpool.conf.sample
sed -i "s|#log_directory = '/tmp/pgpool_logs'|log_directory = '/var/log/pgpool'|" src/sample/pgpool.conf.sample
find . -type f -name "*.sgml" -exec sed -i 's/tutorial-watchdog-changing-automatic-register-in-recovery/changing-automatic-register-in-recovery/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/tutorial-watchdog-integrating-external-lifecheck/watchdog-integrating-external-lifecheck/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/tutorial-watchdog-external-lifecheck-get-nodes/watchdog-external-lifecheck-get-nodes/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/tutorial-watchdog-restrictions-down-watchdog-mode/watchdog-restrictions-down-watchdog-mode/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/tutorial-watchdog-restrictions-down-watchdog-require-restart/restrictions-down-watchdog-require-restart/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/tutorial-watchdog-restrictions-active-take-time/watchdog-restrictions-active-take-time/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/tutorial-watchdog-restrictions-active-take-time/cluster-pgpool-config-online-recovery/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/runtime-config-writing-queries-may-affect-load-balancing/writing-queries-may-affect-load-balancing/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/runtime-config-load-balancing-in-streaming-replication/load-balancing-in-streaming-replication/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/example-dml-adaptive-object-relationship-list-1/example-dml-adaptive-object-relationship/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/example-cluster-pgpool-config-online-recovery/example-cluster-pgpool-online-recovery/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/runtime-in-memory-query-cache-memcached-config/in-memory-query-cache-memcached-config/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/guc-allow-multiple-failover-requests-from-node/allow-multiple-failover-requests-from-node/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/example-cluster-pgpool-config-listen-addresses/example-cluster-config-listen-addresses/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/example-cluster-pgpool-config-backend-settings/example-cluster-config-backend-settings/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/session-level-load-balancing-vs-statement-level-load-balancing/session-level-vs-statement-level-balancing/g' {} +
find . -type f -name "*.sgml" -exec sed -i 's/example-replication-mode-table-postgresql-config/replication-mode-table-postgresql-config/g' {} +

cd ../



git add -A
git commit -m "Apply patch pool.h pgpool.conf.sample DOC"


git remote add origin git@github.com:antioff/pgpool-II.git
git branch -M main
git push -u origin main

git checkout upstream
git push --set-upstream origin upstream
git checkout main




