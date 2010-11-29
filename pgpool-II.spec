%def_with	devel
%define		pgpool_configdir    %_sysconfdir/pgpool.d
%define		pgpool_piddir    %_var/run/pgpool
%define		pgpool_logdir    %_logdir/pgpool
%define		PGSQL   pgsql

Name:		pgpool-II 
Version:	2.3.3
Release:        alt2 
Summary:	pgpool is a connection pool/replication server for PostgreSQL	
License: 	BSD
Group: 		Databases
Url:		http://pgfoundry.org/projects/pgpool
Source:		%name-%version.tar.gz
Source1:        pgpool.init
Source2:	pgpool.conf
Patch0:		0001-Fix-EINTR-for-all-cases-in-health-check.patch

BuildRequires: flex gcc-c++ postgresql-devel


%package        devel
Summary:        header files for  %name.
Group:          Databases

%prep
%setup -q
%patch0 -p2

%build
%configure	--includedir=/usr/include/pgsql
%make_build

%install
/usr/sbin/groupadd -g 46 postgres || :
/usr/sbin/useradd -M -o -r -d %_localstatedir/%PGSQL -s /dev/null \
        -c "PostgreSQL Server, slony1, pgpool daemon" -u 46 postgres -g postgres || :

%make DESTDIR=%buildroot install
%__install -d -m 700 %buildroot%pgpool_configdir
%__install -p -m755 -D %SOURCE1 %buildroot%_initdir/pgpool
%__install -p -m755 -D %SOURCE2 %buildroot%pgpool_configdir/pgpool.conf 

%__mkdir_p %buildroot{%pgpool_piddir,%pgpool_logdir,%pgpool_configdir}
mv %buildroot%_sysconfdir/pgpool.conf.sample %buildroot%pgpool_configdir/


#ln -s %pgpool_configdir/pgpool.conf %buildroot%_sysconfdir/pgpool.conf
%pre
/usr/sbin/groupadd -g 46 postgres || :
/usr/sbin/useradd -M -o -r -d %_localstatedir/%PGSQL -s /dev/null \
	-c "PostgreSQL Server and slony1 daemon" -u 46 postgres -g postgres || :

%post
%post_service pgpool

%files
%_bindir/*
%_man8dir/*
%_libdir/*

%_datadir/%name
%_initdir/pgpool
%pgpool_configdir/pgpool.conf
#%_sysconfdir/pgpool.conf

%attr(750,root,postgres) %dir %pgpool_configdir
%attr(770,root,postgres) %dir %pgpool_piddir
%attr(770,root,postgres) %dir %pgpool_logdir

%files devel
%_includedir/%PGSQL

%description
pgpool-II is a middleware that works between PostgreSQL servers and a PostgreSQL database client
%description    devel
header files for %name.


%changelog
* Mon Nov 29 2010 Alexander V Openkin <open@altlinux.ru> 2.3.3-alt1
- 2.3.3 release 

* Wed Oct 14 2009 Alexander V Openkin <open@altlinux.ru> 2.2.5-alt1
- 2.2.5 release

* Fri May 22 2009 Alexander V Openkin <open@altlinux.ru> 2.2.2-alt2
- New init script read the /etc/pgpool.d directory and running many pgpool instance 

* Tue May 05 2009 Alexander V Openkin <open@altlinux.ru> 2.2.2-alt1
- 2.2.2 release, new init script. 

* Wed Oct 22 2008 Alexander V Openkin <open@altlinux.ru> 2.1-alt1
- 2.1 release 

* Wed Sep 05 2007 Alexander V Openkin <open@altlinux.ru> 1.2-alt1
- changed init script (logging to syslog) 

* Tue Aug 28 2007 Alexander V Openkin <open@altlinux.ru> 1.2-alt0.4
- 1.2 release 

* Fri Jul 20 2007 Alexander V Openkin <open@altlinux.ru> 1.1.1-alt0.2
- pool_process_query.c: Fix kind mismatch error when load_balance_mode is true

