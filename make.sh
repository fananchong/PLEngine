#!/bin/bash

curpath=$PWD

set -ex

cd $curpath/src/common_cplus/build
./make-docker.sh

cd $curpath/src/build
./make-docker.sh

cd $curpath/test/build
./make-docker.sh
