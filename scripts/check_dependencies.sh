#!/bin/bash

SOURCE_DIR="$(dirname "$0")/.."
CMAKE_DIR="$SOURCE_DIR/cmake"

cmake -S "$SOURCE_DIR" -P "$CMAKE_DIR/CheckDependencies.cmake"