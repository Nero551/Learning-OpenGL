#!/bin/sh
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

cmake -S "$SCRIPT_DIR" \
      -B "$SCRIPT_DIR/build" \
      -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE=$HOME/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build "$SCRIPT_DIR/build"