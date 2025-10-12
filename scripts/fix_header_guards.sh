#!/usr/bin/env bash

# --- Configuration ---
CLANG_TIDY="/opt/homebrew/opt/llvm/bin/clang-tidy"
BUILD_DIR="build"

# --- Argument Parsing ---
FIX_MODE=""
TARGET_FILE=""

usage() {
  echo "Usage: $0 [-f] <header_file>" >&2
  echo "  -f: Apply fixes directly to the file (uses -fix)." >&2
  exit 1
}

while getopts "f" opt; do
  case $opt in
    f) FIX_MODE="-fix" ;;
    *) usage ;;
  esac
done

shift "$((OPTIND-1))"

if [ -z "$1" ]; then
  usage
fi
TARGET_FILE="$1"

# --- Execution ---

export COMPILATION_DATABASE_DIR="$BUILD_DIR"

if [ ! -f "$TARGET_FILE" ]; then
  echo "Error: File not found: $TARGET_FILE" >&2
  exit 1
fi

if [ ! -x "$CLANG_TIDY" ]; then
  echo "Error: Clang-Tidy not found at: $CLANG_TIDY" >&2
  exit 1
fi

echo "--- Running Clang-Tidy on $TARGET_FILE ${FIX_MODE} ---"

"$CLANG_TIDY" \
  -fix-errors \
  -checks='llvm-header-guard' \
  "$FIX_MODE" \
  "$TARGET_FILE" \
  -- \
  -x c++ \
  -std=c++20 \
  -DFP_PLUS_PLUS_INCLUDED_FROM_FP_FP \
  -Iinclude

# Remove the export if you want the variable only for this script
unset COMPILATION_DATABASE_DIR

if [ $? -ne 0 ]; then
  echo "--- Clang-Tidy encountered an error (exit code $?) ---"
else
  echo "--- Clang-Tidy finished successfully ---"
fi
