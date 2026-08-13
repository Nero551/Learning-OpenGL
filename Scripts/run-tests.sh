#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/Scripts/build-tests.sh"

echo "🧪 Running Tests..."
"$ROOT/Tests/build-tests/UnitTests"

echo "✅ All tests passed."