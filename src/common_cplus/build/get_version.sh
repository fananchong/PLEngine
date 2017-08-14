#!/bin/bash

id=`git rev-list HEAD | head -1`
dt=`date +'%Y/%m/%d %H:%M:%S'`
out_file=../../../deps/include/plengine/version.h

echo '#ifndef __VERSION_H__' > $out_file
echo '#define __VERSION_H__' >> $out_file
echo '#define APP_VERSION "'$id'"' >> $out_file
echo '#define APP_BUILD_TIME "'$dt'"' >> $out_file
echo '#endif' >> $out_file

