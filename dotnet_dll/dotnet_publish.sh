#!/bin/bash -xe

if [ $# != 1 ]; then
    echo 'need target solution. e.g. invokee_test'
    exit 255
fi

cd $(dirname $0)
pwd
SLN=${1}

dotnet publish --force --self-contained true -o "./publish_${SLN}"  -c Release -r linux-x64  ./${SLN}/${SLN}.csproj

cd -
