#!/bin/sh

cmake -B build-tests -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja -C build-tests