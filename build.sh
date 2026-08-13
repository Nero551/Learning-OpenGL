#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"
VCPKG="$ROOT/vcpkg"

echo "📦 Checking vcpkg..."

if [ ! -f "$VCPKG/vcpkg" ]; then
    echo "📥 Initializing vcpkg..."

    git -C "$ROOT" submodule update --init --recursive

    echo "🔧 Bootstrapping vcpkg..."
    "$VCPKG/bootstrap-vcpkg.sh"
fi

echo "🔨 Building..."

cmake -S "$ROOT" \
      -B "$ROOT/build" \
      -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE="$VCPKG/scripts/buildsystems/vcpkg.cmake"
      -DVCPKG_MANIFEST_DIR="$ROOT"

cmake --build "$ROOT/build"

echo "✅ Built."