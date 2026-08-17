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

echo "✅ vcpkg Initialized"