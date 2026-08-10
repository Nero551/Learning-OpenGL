#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/build.sh"

echo "🧪 Running..."
"$ROOT/build/Nova"

