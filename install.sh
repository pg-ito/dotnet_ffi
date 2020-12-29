#!/bin/bash -xe

# e.g. export LIBCORECLR_CTL_DIR=/usr/local/lib/
LIBCORECLR_CTL_DIR=${LIBCORECLR_CTL_DIR:-/usr/local/lib/}

# e.g. export EXTENSION_DIR=/usr/local/lsws/lsphp7_4_12/lib/php/extensions/no-debug-non-zts-20190902/
echo ${EXTENSION_DIR}
EXTENSION_DIR=${EXTENSION_DIR:-/usr/local/lib/php/extensions/}

# e.g. export PHP_INI_FPATH=/usr/local/lsws/lsphp7_4_12/lib/php.ini
PHP_INI_FPATH=${PHP_INI_FPATH:-/etc/php/php.ini}
echo ${PHP_INI_FPATH}

DOTNET_FFI_INI_FILE=dotnet_ffi.ini
cat << EOM
LIBCORECLR_CTL_DIR  ${LIBCORECLR_CTL_DIR}
EXTENSION_DIR       ${EXTENSION_DIR}
PHP_INI_FPATH       ${PHP_INI_FPATH}

========== ${DOTNET_FFI_INI_FILE} ===========
$(cat ${DOTNET_FFI_INI_FILE})
EOM


sudo cp -ipav coreclrhost ${LIBCORECLR_CTL_DIR}

sudo cp -ipav modules/dotnet_ffi.so ${EXTENSION_DIR}

# grep '^\[dotnet_ffi\]' ${PHP_INI_FPATH}
# INI_CONF_EXISTS=$?
# echo "INI_CONF_EXISTS: ${INI_CONF_EXISTS}"

if [ $(grep '^\[dotnet_ffi\]' ${PHP_INI_FPATH}|wc -l) -eq 0 ];then
  sudo bash -c "cat dotnet_ffi.ini >> ${PHP_INI_FPATH}"
  echo -e "added dotnet_ffi config to ${INI_CONF_EXISTS}\n"
fi


echo -e "extension installed. Need reboot your httpd server.\n"



