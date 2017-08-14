#!/bin/bash

set -e

cd ../../src/common_cplus/build/
./make-docker.sh

cd ../../../test/build/
./make-docker.sh







