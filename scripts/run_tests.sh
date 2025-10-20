#!/usr/bin/env bash
REPO_ROOT=$(git rev-parse --show-toplevel 2>/dev/null)
if [ -z "$REPO_ROOT" ]; then
  echo "Error: Not inside a Git repository." >&2
  exit 1
fi
cd "$REPO_ROOT" || { echo "Error: Failed to change to repository root '$REPO_ROOT'." >&2; exit 1; }

QUIET_CTEST=false   # Corresponds to ctest's --quiet
VERBOSE_CTEST=false # Corresponds to ctest's -V (more verbose)
PRINT_GAP=false      # Print 30 line gap before running tests

if command -v nproc &>/dev/null; then
  JOBS=$(nproc) # Linux
elif [[ "$(uname)" == "Darwin" ]]; then
  JOBS=$(sysctl -n hw.ncpu) # macOS
else
  JOBS=1
fi

TARGET="all"

while getopts "qsvgj:t:" opt; do
  case $opt in
    q) QUIET_CTEST=true ;;   # When -q is provided, set ctest to be quiet (--quiet)
    v) VERBOSE_CTEST=true ;; # When -s is provided, set ctest to be short/verbose (-V)
    g) PRINT_GAP=true ;;    # Changed to an "no-gap" flag for more common UX, or keep original logic
    j) JOBS=$OPTARG ;;
    t) TARGET=$OPTARG ;;
    *) echo "Usage: $0 [-q] [-s] [-g] [-j jobs] [-t target]" >&2; exit 1 ;;
  esac
done

if [ "$PRINT_GAP" = true ]; then
  printf "\n%.0s" {1..30}
fi

BUILD_CMD=("cmake" "--build" "build" "--target" "${TARGET}" "--" "-j${JOBS}")
CTEST_CMD=("ctest" "--test-dir=build")

if [ "$VERBOSE_CTEST" = true ]; then
  CTEST_CMD+=("-V")
fi

if [ "$QUIET_CTEST" = true ]; then
  CTEST_CMD+=("--quiet")
fi

echo "Running build command: ${BUILD_CMD[*]}"
if ! "${BUILD_CMD[@]}"; then
    echo "Error: Build failed." >&2
    exit 1
fi

echo "Running ctest command: ${CTEST_CMD[*]}"
"${CTEST_CMD[@]}"
