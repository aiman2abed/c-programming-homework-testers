#!/usr/bin/env bash
set -euo pipefail

if [ $# -ne 1 ]; then
  echo "Usage: $0 HW5_<StudentID>.zip"
  exit 1
fi

ZIPFILE="$1"

if [[ ! "$ZIPFILE" =~ ^HW5_[0-9]+\.zip$ ]]; then
  echo "✗ ERROR: ZIP file must be named like 'HW5_123456789.zip'"
  exit 2
fi

WORKDIR=".submission"
rm -rf "$WORKDIR"
mkdir -p "$WORKDIR"

BASE_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MANIFEST="$BASE_DIR/hw5/HW5_tester/tests_all.json"
RUNNER="$BASE_DIR/scripts/HW5_test_runner.py"

echo "→ Unzipping $ZIPFILE → $WORKDIR/"
unzip -q "$ZIPFILE" -d "$WORKDIR"

for src in hw5_q1.c hw5_q2.c hw5_q3.c hw5_q4.c hw5_q5.c; do
  if [ ! -f "$WORKDIR/$src" ]; then
    echo "✗ ERROR: $src not found inside the archive"
    exit 3
  fi
  exe="${src%.c}"
  echo "→ Compiling $src"
  gcc -std=c99 -Wall -Werror -o "$WORKDIR/$exe" "$WORKDIR/$src"
done

echo "→ Running tests"
python3 "$RUNNER" "$WORKDIR" "$MANIFEST"

rm -rf "$WORKDIR"
echo "✓ Done."
