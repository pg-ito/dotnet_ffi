#!/bin/bash -xe

cd $(dirname $0)

CURRENT_DIR=$(pwd)
echo ${CURRENT_DIR}



# e.g. export LIBCORECLR_CTL_DIR=/usr/local/lib/
LIBCORECLR_CTL_DIR=${LIBCORECLR_CTL_DIR:-/usr/local/lib/}

# e.g. export EXTENSION_DIR=/usr/local/lsws/lsphp7_4_12/lib/php/extensions/no-debug-non-zts-20190902/
echo ${EXTENSION_DIR}
EXTENSION_DIR=${EXTENSION_DIR:-/usr/lib/php/20190902/}

# e.g. export PHP_INI_FPATH=/usr/local/lsws/lsphp7_4_12/lib/php.ini
PHP_INI_FPATH=${PHP_INI_FPATH:-/etc/php/7.4/cli/php.ini}
echo ${PHP_INI_FPATH}

# e.g. export PHP_ADDITIONAL_INI_DIR=/etc/php/7.4/apache2/conf.d 
PHP_ADDITIONAL_INI_DIR=${PHP_ADDITIONAL_INI_DIR:-/etc/php/7.4/apache2/conf.d/}
echo ${PHP_ADDITIONAL_INI_DIR}

DOTNET_FFI_INI_FILE=dotnet_ffi.ini
cat << EOM
LIBCORECLR_CTL_DIR      ${LIBCORECLR_CTL_DIR}
EXTENSION_DIR           ${EXTENSION_DIR}
PHP_INI_FPATH           ${PHP_INI_FPATH}
PHP_ADDITIONAL_INI_DIR  ${PHP_ADDITIONAL_INI_DIR}
========== ${DOTNET_FFI_INI_FILE} ===========
$(cat ${DOTNET_FFI_INI_FILE})
EOM


sudo cp -ipav coreclrhost ${LIBCORECLR_CTL_DIR}

sudo cp -ipav modules/dotnet_ffi.so ${EXTENSION_DIR}


# if [ $(grep '^\[dotnet_ffi\]' ${PHP_INI_FPATH}|wc -l) -eq 0 ];then
#   sudo bash -c "cat dotnet_ffi.ini >> ${PHP_INI_FPATH}"
#  echo -e "added dotnet_ffi config to ${INI_CONF_EXISTS}\n"
# fi

# sudo cp -ipav ${DOTNET_FFI_INI_FILE} ${PHP_ADDITIONAL_INI_DIR}

INI_VALUES=$(cat <<EOM
[dotnet_ffi]
extension=dotnet_ffi.so
; dotnet_ffi.libcoreclr_file_path=/PATH/TO/PUBLISHED_DOTNET_PROJECT/libcoreclr.so
dotnet_ffi.libcoreclr_file_path=${CURRENT_DIR}/dotnet_dll/publish_invokee_test/libcoreclr.so
; dotnet_ffi.target_project_name="DOTNET_PROJECT_NAME, Version=1.0.0.0"
dotnet_ffi.target_project_name="invokee_test, Version=1.0.0.0"
; dotnet_ffi.target_class_name="INVOKE_TARGET_NAMESPACE.INVOKE_TARGET_CLASS"
dotnet_ffi.target_class_name="invokee_test.InvokeeTest"
; static Class Method names
dotnet_ffi.target_method_invoke_ret_str_arg_str="return_str_arg_str"
dotnet_ffi.target_method_invoke_ret_s64_arg_s64="return_s64_arg_s64"
dotnet_ffi.target_method_invoke_ret_dbl_arg_dbl="return_double_arg_double"

EOM
)

echo "${INI_VALUES}"

sudo bash -c "echo '${INI_VALUES}' > ${PHP_ADDITIONAL_INI_DIR}${DOTNET_FFI_INI_FILE}"

echo -e "extension installed. Need reboot your httpd server.\n"


cd -

