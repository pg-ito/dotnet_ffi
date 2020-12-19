#!/bin/bash -xe

echo build and run
make -j4 

/usr/local/php7_2_24dev/bin/php -d extension=./modules/dotnet_ffi.so -f ext_test.php 
