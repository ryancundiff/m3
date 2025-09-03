#!/bin/bash

# Build script for Linux/MacOS.
# Create a build directory and run CMake.

set -e

# Check if build directory exists.
if [ ! -d build ]; then
  mkdir build
fi

# Run CMake to configure and build.
cmake -S . -B build
cmake --build build --config Release