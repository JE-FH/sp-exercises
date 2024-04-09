#!/usr/bin/env bash
set -e

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do
  HERE=$(cd -P $(dirname "$SOURCE") >/dev/null 2>&1 && pwd)
  SOURCE=$(readlink "$SOURCE")
  [[ "$SOURCE" != /* ]] && SOURCE="$HERE/$SOURCE"
done
HERE=$(cd -P $(dirname "$SOURCE") > /dev/null 2>&1 && pwd)

NAME=$(basename "$HERE")
DEST="/tmp/$NAME"
rm -Rf "$DEST"
cp -Rp . "$DEST"
rm -Rf "$DEST"/cmake-* "$DEST/build" "$DEST/.git" "$DEST/.idea" "$DEST/.gitignore"

(cd /tmp; zip -r9 "$NAME.zip" "$NAME")
echo "Done: $DEST.zip"
