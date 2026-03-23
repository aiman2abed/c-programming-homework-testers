#!/usr/bin/env bash
set -euo pipefail

if [ $# -ne 1 ]; then
  echo "Usage: $0 HW4_<StudentID>.zip"
  exit 1
fi

ZIPFILE="$1"

if [[ ! "$ZIPFILE" =~ ^HW4_[0-9]+\.zip$ ]]; then
  echo "✗ ERROR: ZIP file must be named like 'HW4_123456789.zip'"
  exit 2
fi

WORKDIR=".submission"
rm -rf "$WORKDIR"
mkdir -p "$WORKDIR"

BASE_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MANIFEST="$BASE_DIR/hw4/HW4_tester/tests_all.json"
RUNNER="$BASE_DIR/scripts/HW4_test_runner.py"

echo "→ Unzipping $ZIPFILE → $WORKDIR/"
unzip -q "$ZIPFILE" -d "$WORKDIR"

if [ ! -f "$WORKDIR/hw4.c" ]; then
  echo "✗ ERROR: hw4.c not found inside the archive"
  exit 3
fi

echo "→ Compiling hw4.c"
gcc -std=c99 -Wall -Werror -lm -o "$WORKDIR/hw4" "$WORKDIR/hw4.c"

echo "→ Running tests"
python3 "$RUNNER" "$WORKDIR/hw4" "$MANIFEST"

rm -rf "$WORKDIR"
echo "✓ Done."
