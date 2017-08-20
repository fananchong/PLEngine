#!/bin/bash

../bin/Release/pnode                    \
    --name=$1                           \
    --py_home_path=../bin/res/py        \
    --py_script_path=./$1/python/       \
    --log_ini_file=../bin/log.ini       \
    --log_with_color                    \
    --py_shell

