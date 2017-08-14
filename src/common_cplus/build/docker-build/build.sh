#!/bin/bash

set -e

docker build -t plengine/build-centos7 ./centos7.3
docker build -t plengine/build-plengine_common ./plengine_common
