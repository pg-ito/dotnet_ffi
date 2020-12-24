#!/bin/bash -xe
PHPFILE=${1:-ext_test.php}
PHPBIN_PATH=${PHPBIN_PATH:-/usr/local/php7_2_24dev/bin/php}
${PHPBIN_PATH} -d extension=./modules/dotnet_ffi.so -f ${PHPFILE} -c dotnet_ffi.ini
