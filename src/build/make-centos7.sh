#!/bin/bash

set -ex

if [ $1 ]; then
    if [ $1 == "rebuild"]; then
        rm -rf obj/linux
    fi
fi

./premake5-linux.sh
make config=debug_x64
make config=release_x64
