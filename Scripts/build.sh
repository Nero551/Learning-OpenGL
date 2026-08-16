#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/Scripts/init-vcpkg.sh"

echo "🔨 Building..."

cmake --preset default -S "$ROOT"

cmake --build --preset default

echo "✅ Built."