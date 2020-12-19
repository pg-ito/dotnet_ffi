#!/bin/bash

PHP_DEBUG=${1:-"yes"}
# ./configure --enable${DEBUG_FLAG}
./configure --enable-dotnet_ffi
