#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/Scripts/init-vcpkg.sh"

echo "🔨 Building Tests..."

cd "$ROOT/Tests"
cmake --preset default
cmake --build --preset default

echo "✅ Built Tests."
