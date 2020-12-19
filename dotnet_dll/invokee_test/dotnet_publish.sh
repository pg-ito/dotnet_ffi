#!/bin/bash -xe

cd $(dirname $0)

dotnet publish --force --self-contained true -o ../publish  -c Release -r linux-x64
ls -alG ../publish
cd -
