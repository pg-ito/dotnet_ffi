#!/bin/bash -xe
PHPFILE=${1:-ext_test.php}
php -f ${PHPFILE} -d extension=modules/dotnet_ffi.so -c dotnet_ffi.ini
