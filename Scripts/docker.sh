#!/bin/sh

set -e

docker build -t nova-dev .

echo "🥳 Built Image"

docker run --rm -it \
    -v "$PWD/CMakeLists.txt:/Nova/CMakeLists.txt" \
    -v "$PWD/CMakePresets.json:/Nova/CMakePresets.json" \
    -v "$PWD/src:/Nova/src" \
    -v "$PWD/Scripts:/Nova/Scripts" \
    -v "$PWD/Tests:/Nova/Tests" \
    -v "$PWD/vcpkg.json:/Nova/vcpkg.json" \
    -v "$PWD/Doxyfile:/Nova/Doxyfile" \
    -v "$PWD/icon.svg:/Nova/icon.svg" \
    -v "$PWD/README.md:/Nova/README.md" \
    -v "$PWD/.clang-format:/Nova/.clang-format" \
    -v "$PWD/.clangd:/Nova/.clangd" \
    -v "$PWD/.git:/Nova/.git" \
    -v nova-vcpkg-cache:/root/.cache/vcpkg \
    nova-dev