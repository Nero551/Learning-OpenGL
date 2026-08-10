#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

echo "🔨 Building..."

cmake -S "$ROOT" \
      -B "$ROOT/build" \
      -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE=$HOME/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build "$ROOT/build"
echo "✅ Built."