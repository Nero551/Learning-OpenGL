#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"
VCPKG="$ROOT/vcpkg"

if [ ! -f "$VCPKG/vcpkg" ]; then
    echo "📥 Initializing vcpkg..."

    git -C "$ROOT" submodule update --init --recursive

    echo "🔧 Bootstrapping vcpkg..."
    "$VCPKG/bootstrap-vcpkg.sh"
fi

echo "🔨 Building Tests..."

cmake --preset default -S "$ROOT/Tests"
cmake --build --preset default

echo "✅ Built Tests."
