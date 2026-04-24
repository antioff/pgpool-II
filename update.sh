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

