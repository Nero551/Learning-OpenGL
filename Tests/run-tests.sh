#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

echo "🔨 Building UnitTests..."
"$ROOT/Tests/build-tests.sh"

echo "🧪 Running UnitTests..."
"$ROOT/Tests/build-tests/UnitTests"

echo "✅ All tests passed."