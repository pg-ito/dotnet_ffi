#!/bin/bash -xe
cd $(dirname $0)

if [ "${1}" == "debug" ];then
  DEBUG_BUILD_FLAG='-DDEBUG=1 -g'
fi

LIB_NAME="libcoreclr_ctlpp"

LIB_DIR="lib"
g++ ${DEBUG_BUILD_FLAG} -O2 -fPIC -std=gnu++1y -c coreclr_ctlpp.cpp -ldl
ar rcs ${LIB_NAME}.a coreclr_ctlpp.o
cp -fpav coreclr_ctlpp.h ../${LIB_DIR}

g++ ${DEBUG_BUILD_FLAG} -O2 --shared -fPIC -std=gnu++1y -o ${LIB_NAME}.so coreclr_ctlpp.cpp -ldl

# cp -fpav ${LIB_NAME}.* ../${LIB_DIR}
# ls -alG
# nm ${LIB_NAME}*
DEBUG_APP_CMD="./${LIB_NAME}_app  ../dotnet_dll/publish_invokee_test/libcoreclr.so"
echo "debug app compiled. usage: ${DEBUG_APP_CMD}"

if [ "${1}" == "debug" ];then
  g++  -ggdb -fsanitize=leak -fno-omit-frame-pointer -static-liblsan -static-libgcc ${DEBUG_BUILD_FLAG} -O2 -fPIC -std=gnu++1y -o ${LIB_NAME}_app coreclr_ctlpp.cpp -ldl
  ${DEBUG_APP_CMD}
fi

cd -
