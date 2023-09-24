#!/bin/bash

SOURCE_DIR="$(dirname "$0")/.."

cd "$SOURCE_DIR"
git submodule update --init --recursive
git submodule update --remote --merge --recursive