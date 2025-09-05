#!/bin/bash

# Build script for Linux/macOS.
# Create a build directory and run CMake.

set -e

# Check if build directory exists.
if [ ! -d build ]; then
  mkdir build
fi

# Run CMake to configure and build.
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release