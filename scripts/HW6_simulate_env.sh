#!/usr/bin/env bash
set -euo pipefail

if [ $# -ne 1 ]; then
  echo "Usage: $0 HW6_<StudentID>.zip"
  exit 1
fi

ZIPFILE="$1"

if [[ ! "$ZIPFILE" =~ ^HW6_[0-9]+\.zip$ ]]; then
  echo "✗ ERROR: ZIP file must be named like 'HW6_123456789.zip'"
  exit 2
fi

WORKDIR=".submission"
rm -rf "$WORKDIR"
mkdir -p "$WORKDIR"

BASE_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MANIFEST="$BASE_DIR/hw6/HW6_tester/tests_all.json"
RUNNER="$BASE_DIR/scripts/HW6_test_runner.py"

echo "→ Unzipping $ZIPFILE → $WORKDIR/"
unzip -q "$ZIPFILE" -d "$WORKDIR"

if [ ! -f "$WORKDIR/hw6.c" ]; then
  echo "✗ ERROR: hw6.c not found inside the archive"
  exit 3
fi

echo "→ Compiling hw6.c"
gcc -std=c99 -Wall -Werror -o "$WORKDIR/hw6" "$WORKDIR/hw6.c"

echo "→ Running tests"
python3 "$RUNNER" "$WORKDIR/hw6" "$MANIFEST"

rm -rf "$WORKDIR"
echo "✓ Done."
