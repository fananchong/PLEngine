#!/bin/bash

set -ex

cp -f /usr/local/lib/*.a /tmp/home/deps/lib_linux

mkdir -p /tmp/home/deps/include/python/linux
cp -f /usr/local/include/python3.6m/*.h /tmp/home/deps/include/python/linux/

mkdir -p /tmp/home/bin/res/py/linux/Lib
cp -rf /usr/local/lib/python3.6/* /tmp/home/bin/res/py/linux/Lib/
