#!/bin/bash -xe
PHPFILE=${1:-ext_test.php}
PHP_PATH=${PHP_PATH:-/usr/bin/}
${PHP_PATH}php -d extension=./modules/dotnet_ffi.so -f ${PHPFILE} -c dotnet_ffi.ini
