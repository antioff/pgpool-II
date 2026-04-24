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

