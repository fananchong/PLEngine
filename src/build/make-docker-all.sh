#!/bin/bash

set -e

cd ../common_cplus/build/
./make-docker.sh

cd ../../build/
./make-docker.sh







