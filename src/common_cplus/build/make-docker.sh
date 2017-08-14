#!/bin/bash

set -ex

cd docker-build
./build.sh

out_path=`pwd`/../../../../

docker run -it --rm -v $out_path:/tmp/home plengine/build-plengine_common /bin/bash "/setup.sh"
