#!/bin/bash -xe
cd $(dirname $0)

LIB_NAME="libcoreclr_ctlpp"


g++ -fPIC -c coreclr_ctlpp.cpp -ldl
ar rcs ${LIB_NAME}.a coreclr_ctlpp.o
g++ --shared -fPIC -o ${LIB_NAME}.so coreclr_ctlpp.cpp -ldl
g++ -fPIC -o ${LIB_NAME}_app coreclr_ctlpp.cpp -ldl
ls -alG
DEBUG_APP_CMD="./${LIB_NAME}_app ../dotnet_dll/publish/libcoreclr.so"
echo "debug app compiled. usage: ${DEBUG_APP_CMD}"

if [ "${1}" == "debug" ];then
  ${DEBUG_APP_CMD}
fi

cd -
