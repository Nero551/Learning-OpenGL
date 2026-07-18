#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

echo "🔨 Building..."
"$ROOT/build.sh"

echo "✅ Built."

echo "🧪 Running..."
"$ROOT/build/Engine"

