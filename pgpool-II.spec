%define sname pgpool
# select postgres version pro-1c-16, 16, 15, 15-1C ...
%define pg_pkg_ver 15


%if "%(echo %pg_pkg_ver | cut -d- -f1)" == "pro"
%define pg_pro 1
%define pg_name postgrespro-%(echo %pg_pkg_ver | cut -d- -f2-)
BuildRequires: %pg_name-devel
%define pg_ver %get_version %pg_name-devel
%define pg_home /opt/pgpro/%(echo %pg_pkg_ver| cut -d- -f2-)
%define pg_include "--with-pgsql=%pg_home"
%else
%define pg_pro 0
%define pg_name postgresql%pg_pkg_ver
BuildRequires: %pg_name-server-devel
%define pg_ver %get_version %pg_name-server-devel
%define pg_home %_usr
%define pg_include " "
%endif
%define pg_v10 %(c=%pg_ver; echo $((${c//.})))

Name: pgpool-II
Version: 4.5.1
Release: alt1
Summary: Pgpool is a connection pooling/replication server for PostgreSQL
License: BSD
Group: Databases
Url: http://www.pgpool.net
Source0: %name-%version.tar

Source1: pgpool.init
Source2: pgpool.service
Source3: pgpool.sysconfig
Source4: pgpool_sudoers.d
Source5: pgpool_tmpfiles.d

Patch0: pgpool_socket_dir_log.patch
Patch1: pgpool_namelen44.patch

BuildRequires: libpq-devel
BuildRequires: flex
BuildRequires: pam-devel
BuildRequires: libmemcached-devel
BuildRequires: libssl-devel
BuildRequires: setproctitle-devel
BuildRequires: openjade
BuildRequires: OpenSP
BuildRequires: libtool
BuildRequires: openssl-devel
BuildRequires: xsltproc
BuildRequires: libxslt
BuildRequires: docbook-style-dsssl
BuildRequires: docbook-style-dsssl-utils
BuildRequires: docbook-dtds
BuildRequires: docbook-style-xsl
BuildRequires: openldap-devel

Requires: postgresql-common
Provides: pgpool2 = %EVR

%description
pgpool-II is a inherited project of pgpool (to classify from
pgpool-II, it is sometimes called as pgpool-I). For those of
you not familiar with pgpool-I, it is a multi-functional
middle ware for PostgreSQL that features connection pooling,
replication and load balancing functions. pgpool-I allows a
user to connect at most two PostgreSQL servers for higher
availability or for higher search performance compared to a
single PostgreSQL server.

%package -n libpcp
Summary: lib files for  %name
Group: System/Libraries
Provides: %name-lib = %EVR
Obsoletes: %name-lib < %EVR

%description -n libpcp
lib files for %name.

%package -n libpcp-devel
Summary: The development files for pgpool-II
Group: Development/C
Provides: %name-devel = %EVR
Obsoletes: %name-devel < %EVR
Requires: libpcp = %EVR

%description -n libpcp-devel
Development headers and libraries for pgpool-II.

%package -n %pg_name-%name
Summary: Postgresql extensions for pgpool-II
Group: Databases
Requires: %pg_name-server

%description -n %pg_name-%name
Postgresql extensions libraries and sql files for pgpool-II.

%prep
%setup
%patch0 -p2
%patch1 -p2

%build
%autoreconf
%configure \
    %pg_include \
    --disable-static \
    --with-pam \
    --with-ldap \
    --with-openssl \
    --disable-rpath \
    --with-memcached=%_includedir/libmemcached \
    --sysconfdir=%_sysconfdir/%sname/

%make
%make_build -C doc

%install
%set_verify_elf_method rpath=relaxed

%if %pg_pro
export PATH=%pg_home/bin:$PATH
%endif

%makeinstall_std

# install to PostgreSQL
%makeinstall_std -C src/sql/pgpool_adm
%makeinstall_std -C src/sql/pgpool-recovery

# From PostgreSQL 9.4 pgpool-regclass.so is not needed anymore
# because 9.4 or later has to_regclass.

%if %pg_v10 <= 93
%makeinstall_std -C src/sql/pgpool-regclass
%endif

# install /etc/rc.d/init.d/pgpool init script
install -d %buildroot%_initdir
install -m 755 %SOURCE1 %buildroot%_initdir/%sname

# install /etc/systemd/system/pgpool.service
install -d %buildroot%_unitdir
install -m 644 %SOURCE2 %buildroot%_unitdir/%sname.service

# install /etc/sysconfig/pgpool OPTS
install -d %buildroot%_sysconfdir/sysconfig
install -m 644 %SOURCE3 %buildroot%_sysconfdir/sysconfig/%sname

# install sudoers.d to allow postgres user to run ip and arping with root privileges without a password
install -d %buildroot%_sysconfdir/sudoers.d
install -m 0644 %SOURCE4 %buildroot%_sysconfdir/sudoers.d/%sname

# install /etc/tmpfiles.d/pgpool_tmpfiles.d
install -d  %buildroot%_tmpfilesdir
install -m 0644 %SOURCE5 %buildroot%_tmpfilesdir/%sname.conf

install -d -m 755 %buildroot%_runtimedir/%sname
install -d  %buildroot%_logdir/%sname
install -d  %buildroot%_datadir/%sname
cp %buildroot%_datadir/%name/* %buildroot%_datadir/%sname/

install -d  %buildroot%_sysconfdir/%sname/sample_scripts
mv %buildroot%_sysconfdir/%sname/failover.sh.sample %buildroot%_sysconfdir/%sname/sample_scripts/failover.sh.sample
mv %buildroot%_sysconfdir/%sname/follow_primary.sh.sample %buildroot%_sysconfdir/%sname/sample_scripts/follow_primary.sh.sample
mv %buildroot%_sysconfdir/%sname/pgpool_remote_start.sample %buildroot%_sysconfdir/%sname/sample_scripts/pgpool_remote_start.sample
mv %buildroot%_sysconfdir/%sname/recovery_1st_stage.sample %buildroot%_sysconfdir/%sname/sample_scripts/recovery_1st_stage.sample
mv %buildroot%_sysconfdir/%sname/replication_mode_recovery_1st_stage.sample %buildroot%_sysconfdir/%sname/sample_scripts/replication_mode_recovery_1st_stage.sample
mv %buildroot%_sysconfdir/%sname/replication_mode_recovery_2nd_stage.sample %buildroot%_sysconfdir/%sname/sample_scripts/replication_mode_recovery_2nd_stage.sample
mv %buildroot%_sysconfdir/%sname/escalation.sh.sample %buildroot%_sysconfdir/%sname/sample_scripts/escalation.sh.sample
mv %buildroot%_sysconfdir/%sname/aws_eip_if_cmd.sh.sample %buildroot%_sysconfdir/%sname/sample_scripts/aws_eip_if_cmd.sh.sample
mv %buildroot%_sysconfdir/%sname/aws_rtb_if_cmd.sh.sample %buildroot%_sysconfdir/%sname/sample_scripts/aws_rtb_if_cmd.sh.sample

cp %buildroot%_sysconfdir/%sname/pcp.conf.sample %buildroot%_sysconfdir/%sname/pcp.conf
cp %buildroot%_sysconfdir/%sname/pgpool.conf.sample %buildroot%_sysconfdir/%sname/pgpool.conf
cp %buildroot%_sysconfdir/%sname/pool_hba.conf.sample %buildroot%_sysconfdir/%sname/pool_hba.conf
touch %buildroot%_sysconfdir/%sname/pool_passwd
touch %buildroot%_sysconfdir/%sname/pgpool_node_id

mkdir html
mv doc/src/sgml/html html/en

# Copy man pages
install -d %buildroot%_man1dir
install doc/src/sgml/man1/*.1 %buildroot%_man1dir

install -d %buildroot%_man3dir
install doc/src/sgml/man3/*.3 %buildroot%_man3dir

install -d %buildroot%_man8dir
install doc/src/sgml/man8/*.8 %buildroot%_man8dir

# nuke libtool archive and static lib
rm -f %buildroot%_libdir/*.{a,la}

%post
%post_service %sname

%preun
%preun_service %sname
%files
%dir %_datadir/%sname
%doc README TODO COPYING INSTALL AUTHORS ChangeLog html src/sample
%_bindir/*
%_datadir/*
%_man1dir/*.1.xz
%_man3dir/*.3.xz
%_man8dir/*.8.xz
%attr(750,root,postgres) %dir %_runtimedir/%sname
%_tmpfilesdir/%sname.conf
%_sysconfdir/sudoers.d/%sname
%_unitdir/%sname.service
%_initdir/%sname
%dir %attr(750,root,postgres) %_sysconfdir/%sname
%attr(640,root,postgres) %config(noreplace) %_sysconfdir/%sname/*
%config(noreplace) %_sysconfdir/sysconfig/%sname
%dir %attr(1775,root,%sname) %_logdir/%sname

%files -n libpcp-devel
%_includedir/*
%_libdir/libpcp.so

%files -n libpcp
%_libdir/libpcp.so.*

%files -n %pg_name-%name
%if %pg_pro
%pg_home/*
%else
%_libdir/pgsql/*
%_datadir/pgsql/extension/*
%endif

%changelog
* Sat Mar 23 2024 Anton Zamilov <az@drevprof.com> %EVR
- 4.5.1
- build for postgres 15
- build for postgrespro 16-1c

* Thu Mar 11 2021 Alexey Shabalin <shaba@altlinux.org> 4.2.2-alt2
- Fixed config files permissions.

* Wed Feb 24 2021 Alexey Shabalin <shaba@altlinux.org> 4.2.2-alt1
- 4.2.2
- Execute service as postgres system user.
- Move old configs to /etc/pgpool dir.

* Sun Feb 07 2021 Alexey Shabalin <shaba@altlinux.org> 4.2.1-alt1
- 4.2.1
- Execute service as pgpool system user.
- Move configs to /etc/pgpool dir.

* Tue Jan 22 2019 Alexey Shabalin <shaba@altlinux.org> 4.0.2-alt1
- 4.0.2
- build for postgresql11

* Wed Aug 29 2018 Grigory Ustinov <grenka@altlinux.org> 3.7.4-alt1.1
- NMU: Rebuild with new openssl 1.1.0.

* Tue Jul 24 2018 Alexey Shabalin <shaba@altlinux.org> 3.7.4-alt1
- 3.7.4
- rename package pgpool-II-lib to libpcp
- rename package pgpool-II-devel to libpcp-devel
- add package postgresql10-pgpool-II with postgresql extension

* Mon Feb 06 2012 Alexander V Openkin <open@altlinux.ru> 3.1.2-alt2
- 3.1.2 init script fixed
hasher
* Thu Feb 02 2012 Alexander V Openkin <open@altlinux.ru> 3.1.2-alt1
- 3.1.2 release

* Thu Jul 28 2011 Alexander V Openkin <open@altlinux.ru> 3.0.4-alt1
- 3.0.4 release

* Wed Mar 09 2011 Alexander V Openkin <open@altlinux.ru> 3.0.3-alt1
- 3.0.3 release

* Fri Sep 24 2010 Konstantin Pavlov <thresh@altlinux.org> 2.3.3-alt0.M40.7
- Apply patch fixing EINTR problem with pgpool health check.
- Log to /var/log/pgpool instead of slow syslog.

* Fri Jul 30 2010 Alexander V Openkin <open@altlinux.ru> 2.2.5-alt0.M40.2
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

