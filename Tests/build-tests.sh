#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

cmake -S "$ROOT/Tests" \
      -B "$ROOT/Tests/build-tests" \
      -G Ninja \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build "$ROOT/Tests/build-tests"