#!/bin/bash -xe

cd $(dirname $0)

LIB_DIR="../lib"
[ ! -e "${LIB_DIR}" ] && mkdir ${LIB_DIR}


cp -fpv coreclr_ctlpp.h ${LIB_DIR}

cd -

