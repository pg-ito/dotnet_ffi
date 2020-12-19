#!/bin/bash -xe

if [ "${1}" == "debug" ];then
  GCC_OPT=""
  OUTPUT_NAME="debug_app"
else
  GCC_OPT="--shared"
  OUTPUT_NAME="libcoreclrctl.so"
fi    

# GCC_OPT=${1:---shared}

g++ ${GCC_OPT} -fPIC -o ${OUTPUT_NAME} coreclr_ctlpp.cpp -ldl

echo "debug app compiled. usage: ./${OUTPUT_NAME}  ../../dotnet_dll/invokee_test/dotnet_dll/libcoreclr.so"
