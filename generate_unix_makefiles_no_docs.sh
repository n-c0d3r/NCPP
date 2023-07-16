#!/bin/sh

if [ ! -d $(dirname "$0")/build/unix_makefiles ]; then
    mkdir -p $(dirname "$0")/build/unix_makefiles
fi

cmake -G "Unix Makefiles" -S . -B $(dirname "$0")/build/unix_makefiles -D NCPP_GENERATE_DOCS=OFF