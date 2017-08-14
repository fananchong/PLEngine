#!/bin/bash

if [ ! -d "../../../deps/lib_linux/release/" ]; then
    mkdir -p ../../../deps/lib_linux/release/
fi
if [ ! -d "../../../deps/lib_linux/debug/" ]; then
    mkdir -p ../../../deps/lib_linux/debug/
fi
if [ -e "../bin/Release/libplengine_common.a" ]; then
    cp -f ../bin/Release/libplengine_common.a ../../../deps/lib_linux/release/libplengine.a
fi
if [ -e "../bin/Debug/libplengine_common.a" ]; then
    cp -f ../bin/Debug/libplengine_common.a ../../../deps/lib_linux/debug/libplengine.a
fi

cp -f ../*.h ../../../deps/include/plengine
