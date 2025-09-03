@echo off

REM Build script for Windows.
REM Create a build directory and run CMake.

REM Check if build directory exists.
if not exist build (
  mkdir build
)

REM Run CMake to configure and build.
cmake -S . -B build
cmake --build build --config Release

pause