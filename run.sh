#!/bin/bash -xe
PHPFILE=${1:-ext_test.php}
/usr/local/php7_2_24dev/bin/php -d extension=./modules/dotnet_ffi.so  -f ${PHPFILE} -c dotnet_ffi.ini
