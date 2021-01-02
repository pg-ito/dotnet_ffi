#!/bin/bash -xe
PHPFILE=${1:-ext_test.php}
PHP_PATH=${PHP_PATH:-/usr/bin/}
${PHP_PATH}php -f ${PHPFILE} -d extension=modules/dotnet_ffi.so -c dotnet_ffi.ini
