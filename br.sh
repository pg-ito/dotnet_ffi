#!/bin/bash -xe
cd $(dirname $0)


echo build and run


coreclrhost/cpheader.sh
/usr/local/php7_2_24dev/bin/phpize
./configure --enable-dotnet_ffi -with-php-config=/usr/local/php7_2_24dev/bin/php-config
make clean 
dotnet_dll/dotnet_publish.sh invokee_test
# dotnet_dll/dotnet_publish.sh fibonacci
coreclrhost/buildlib.sh

make -j6 
# ldd modules/dotnet_ffi.so
# nm modules/dotnet_ffi.so

# /usr/local/php7_2_24dev/bin/php -d extension=./modules/dotnet_ffi.so -f ext_test.php 
./run.sh

cd -
