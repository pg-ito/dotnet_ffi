#!/bin/bash -xe

cd $(dirname $0)

dotnet publish --force --self-contained true -o dotnet_dll  -c Release -r linux-x64

cd -
