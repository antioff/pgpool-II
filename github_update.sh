#git push origin --delete $(git ls-remote --refs origin postgres* | cut -d$'\t' -f2)
git add -A
git commit -m "Update"
gear-create-tag -f -n "postgrespro-1c-18-v$PGPOOL_VER" -s pgver=postgrespro-1c-18
gear-create-tag -f -n "postgresql17-$PGPOOL_VER" -s pgver=postgresql17
git push
git push origin --force --tags
