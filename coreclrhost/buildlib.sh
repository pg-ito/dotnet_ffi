#!/bin/bash -xe
cd $(dirname $0)

LIB_NAME="libcoreclr_ctlpp"

LIB_DIR="lib"
g++ -O3 -fPIC -c coreclr_ctlpp.cpp -ldl
ar rcs ${LIB_NAME}.a coreclr_ctlpp.o
cp -fpav coreclr_ctlpp.h ../${LIB_DIR}

g++ -O3 --shared -fPIC -o ${LIB_NAME}.so coreclr_ctlpp.cpp -ldl
g++ -O3 -fPIC -o ${LIB_NAME}_app coreclr_ctlpp.cpp -ldl
cp -fpav ${LIB_NAME}.* ../${LIB_DIR}
# ls -alG
# nm ${LIB_NAME}*
DEBUG_APP_CMD="./${LIB_NAME}_app ../dotnet_dll/publish/libcoreclr.so"
echo "debug app compiled. usage: ${DEBUG_APP_CMD}"

if [ "${1}" == "debug" ];then
  ${DEBUG_APP_CMD}
fi

cd -
