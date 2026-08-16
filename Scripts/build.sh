#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/Scripts/init-vcpkg.sh"

echo "🔨 Building..."

export VCPKG_DISABLE_METRICS=1

cmake --preset default -S "$ROOT"

cmake --build --preset default

echo "✅ Built."