#!/bin/sh
set -e

echo "📦 Installing Nova system dependencies..."

sudo pacman -S --needed \
    base-devel \
    clang \
    ccache \
    ninja \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkgconf \
    autoconf \
    autoconf-archive \
    automake \
    libtool

echo "🔧 Checking CMake..."

CMAKE_VERSION="4.4.2"

if cmake --version 2>/dev/null | grep -q "cmake version $CMAKE_VERSION"; then
    echo "✅ CMake $CMAKE_VERSION already installed."
else
    echo "📥 Installing CMake $CMAKE_VERSION..."

    curl -L \
        "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.sh" \
        -o /tmp/cmake.sh

    chmod +x /tmp/cmake.sh

    sudo /tmp/cmake.sh \
        --skip-license \
        --prefix=/usr/local

    rm /tmp/cmake.sh

    echo "✅ CMake installed."
fi

echo "🔍 Verifying tools..."

command -v clang
command -v clang++
command -v ninja
command -v git
command -v cmake

echo "🥳 Nova development environment is ready!"
