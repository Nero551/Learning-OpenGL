#!/bin/sh
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

cmake -S "$SCRIPT_DIR" \
      -B "$SCRIPT_DIR/build-tests" \
      -G Ninja \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build "$SCRIPT_DIR/build-tests"