#!/bin/bash

set -e

cd docker-build
./build.sh

out_path=`pwd`/../../../

docker run -it --rm -v $out_path:/tmp/home plengine/build-plengine_src /bin/bash "/setup.sh"
