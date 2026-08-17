#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/scripts/build-tests.sh"

echo "🧪 Running Tests..."
"$ROOT/Tests/build-tests/UnitTests"

echo "✅ All tests passed."