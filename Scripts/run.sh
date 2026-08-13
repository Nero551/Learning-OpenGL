#!/bin/sh
set -e

ROOT="$(git rev-parse --show-toplevel)"

"$ROOT/Scripts/build.sh"

echo "🧪 Running..."
"$ROOT/build/Nova"

