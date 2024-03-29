/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_dotnet_ffi.h"

// #include "coreclrhost/coreclr_ctlpp.h"
#include "lib/coreclr_ctlpp.h"





/* If you declare any globals in php_dotnet_ffi.h uncomment this: */
ZEND_DECLARE_MODULE_GLOBALS(dotnet_ffi)


/* True global resources - no need for thread safety here */
static int le_dotnet_ffi;

zend_class_entry *dotnet_ffi_entry_ce;

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
    ZEND_PARSE_PARAMETERS_START(0, 0) \
    ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("dotnet_ffi.libcoreclr_file_path",      "/mnt/d/proj/dotnet_invoke/php-src72/php-src-php-7.2.24/ext/dotnet_ffi/dotnet_dll/publish/libcoreclr.so", PHP_INI_SYSTEM, OnUpdateString, libcoreclr_file_path, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_project_name",      "invokee_test, Version=1.0.0.0", PHP_INI_SYSTEM, OnUpdateString, target_project_name, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_class_name",      "invokee_test.InvokeeTest", PHP_INI_SYSTEM, OnUpdateString, target_class_name, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_method_invoke_ret_str_arg_str",     "InvokeReturnString", PHP_INI_SYSTEM, OnUpdateString, target_method_invoke_ret_str_arg_str, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_method_invoke_ret_s64_arg_s64",     "return_s64_arg_s64", PHP_INI_SYSTEM, OnUpdateString, target_method_invoke_ret_s64_arg_s64, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_method_invoke_ret_dbl_arg_dbl",     "return_double_arg_double", PHP_INI_SYSTEM, OnUpdateString, target_method_invoke_ret_dbl_arg_dbl, zend_dotnet_ffi_globals, dotnet_ffi_globals)
	STD_PHP_INI_ENTRY("dotnet_ffi.target_method_invoke_ret_s64_arg_str",     "return_s64_arg_str", PHP_INI_SYSTEM, OnUpdateString, target_method_invoke_ret_s64_arg_str, zend_dotnet_ffi_globals, dotnet_ffi_globals)
PHP_INI_END()


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ret_s64_arg_str, 0, 2, IS_LONG, 0)
    ZEND_ARG_INFO(0, string_arg1)
ZEND_END_ARG_INFO()
PHP_METHOD(DotnetFFI, ret_s64_arg_str)
{
	char *arg1 = NULL;
	size_t arg1_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg1, &arg1_len) == FAILURE) {
		return;
	}

	int hr=-1;
	char *retString = NULL;
	int strLen = 0;
	zend_long res = invoke_ret_s64_arg_str(&hr, arg1, INI_STR("dotnet_ffi.target_method_invoke_ret_s64_arg_str"));
	if(hr < 0){
		DOTNET_FFI_ERRLOG("invoke_ret_s64_arg_str Fail hr: %d\n",hr);
		return;
	}
	RETURN_LONG(res);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ret_dbl_arg_dbl, 0, 1, IS_DOUBLE, 0)
    ZEND_ARG_INFO(0, double_arg1)
ZEND_END_ARG_INFO()
PHP_METHOD(DotnetFFI, ret_dbl_arg_dbl)
{
	double arg;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &arg) == FAILURE) {
		return;
	}
	int hr=-1;
	double res = InvokeReturnDouble(&hr, arg);
	if(hr < 0){
		DOTNET_FFI_ERRLOG("InvokeReturnDouble Fail hr: %d\n",hr);
		return;
	}
	RETURN_DOUBLE(res);
}


ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ret_s64_arg_s64, 0, 1, IS_LONG, 0)
    ZEND_ARG_INFO(0, long_arg1)
ZEND_END_ARG_INFO()
PHP_METHOD(DotnetFFI, ret_s64_arg_s64)
{
	zend_long arg;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &arg) == FAILURE) {
		return;
	}
	int hr=-1;
	zend_long res = invoke_ret_s64_arg_s64(&hr, arg, INI_STR("dotnet_ffi.target_method_invoke_ret_s64_arg_s64"));
	if(hr < 0){
		DOTNET_FFI_ERRLOG("ret_int64_arg_int64 Fail hr: %d\n",hr);
		return;
	}
	RETURN_LONG(res);
}
/*
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null)
*/
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ret_s64_arg_s64_s64, 0, 2, IS_LONG, 0)
    ZEND_ARG_INFO(0, long_arg1)
    ZEND_ARG_INFO(0, long_arg2)
ZEND_END_ARG_INFO()

PHP_METHOD(DotnetFFI, ret_s64_arg_s64_s64)
{
	zend_long arg1 = 0;
	zend_long arg2 = 0;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &arg1, &arg2) == FAILURE) {
		return;
	}
	int hr=-1;
	zend_long result = InvokeReturnInt64(&hr, arg1, arg2);
	if(hr < 0){
		DOTNET_FFI_ERRLOG("InvokeReturnInt64 Fail hr: %d\n",hr);
		return;
	}
	RETURN_LONG(result);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ret_str_arg_str, 0, 2, IS_STRING, 0)
    ZEND_ARG_INFO(0, string_arg1)
ZEND_END_ARG_INFO()
PHP_METHOD(DotnetFFI, ret_str_arg_str)
{
	char *arg1 = NULL;
	size_t arg1_len;


	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg1, &arg1_len) == FAILURE) {
		return;
	}

	int hr=-1;
	char *retString = NULL;
	int strLen = 0;
	invoke_ret_str_arg_str(&hr, arg1, arg1_len, &retString, &strLen,  INI_STR("dotnet_ffi.target_method_invoke_ret_str_arg_str"));
	if(hr < 0){
		DOTNET_FFI_ERRLOG("invoke_ret_str_arg_str Fail hr: %d\n",hr);
		free(retString);
		return;
	}
	
	zend_string *result = strpprintf(0, "%s", retString);
	free(retString);
	RETURN_STR(result);
}

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ret_str_arg_str_multi, 0, 2, IS_STRING, 0)
    ZEND_ARG_INFO(0, string_arg1)
	ZEND_ARG_INFO(0, string_arg2)
ZEND_END_ARG_INFO()
PHP_METHOD(DotnetFFI, ret_str_arg_str_multi)
{
	char *arg1 = NULL;
	size_t arg1_len;

	char *methodName = NULL;
	size_t methodName_len;


	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &arg1, &arg1_len, &methodName, &methodName_len) == FAILURE) {
		return;
	}


	int hr=-1;
	char *retString = NULL;
	int strLen = 0;
	invoke_ret_str_arg_str_multi(&hr, arg1, arg1_len, &retString, &strLen, methodName);
	if(hr < 0){
		DOTNET_FFI_ERRLOG("invoke_ret_str_arg_str_multi Fail hr: %d\n",hr);
		free(retString);
		return;
	}
	
	zend_string *result = strpprintf(0, "%s", retString);
	free(retString);
	RETURN_STR(result);
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/





/* {{{ php_dotnet_ffi_init_globals  */


static void php_dotnet_ffi_init_globals(zend_dotnet_ffi_globals *dotnet_ffi_globals)
{
	dotnet_ffi_globals->libcoreclr_file_path = NULL;
}

static const zend_function_entry dotnet_ffi_funcs_entries[] = {
    PHP_ME(DotnetFFI, ret_s64_arg_s64, arginfo_ret_s64_arg_s64, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(DotnetFFI, ret_str_arg_str, arginfo_ret_str_arg_str, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(DotnetFFI, ret_str_arg_str_multi, arginfo_ret_str_arg_str_multi, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(DotnetFFI, ret_s64_arg_s64_s64, arginfo_ret_s64_arg_s64_s64, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(DotnetFFI, ret_dbl_arg_dbl, arginfo_ret_dbl_arg_dbl, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(DotnetFFI, ret_s64_arg_str, arginfo_ret_s64_arg_str, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
    PHP_FE_END
};

int php_dotnet_ffi_core_clr_initialize(){
	// load ini settings
	const char* clrPath = INI_STR("dotnet_ffi.libcoreclr_file_path");
	int hr = LoadClr(clrPath);

	if(hr<0){
		fprintf(stderr, "DOTNET_FFI_ERROR! %s:%d:%s(): LoadClr erro: %d", __FILE__, __LINE__, __func__, hr);
		return hr;
	}
	hr = InitClr();
	if(hr<0){
		fprintf(stderr, "DOTNET_FFI_ERROR! %s:%d:%s(): InitClr erro: %d", __FILE__, __LINE__, __func__, hr);
		return hr;
	}

	const char* projectName = INI_STR("dotnet_ffi.target_project_name");
	const char* className = INI_STR("dotnet_ffi.target_class_name");
	SetTargtClass(projectName, className);
	return hr;
}


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(dotnet_ffi)
{
	ZEND_INIT_MODULE_GLOBALS(dotnet_ffi, php_dotnet_ffi_init_globals, NULL)
	/* If you have INI entries, uncomment these lines */
	REGISTER_INI_ENTRIES();
	php_dotnet_ffi_core_clr_initialize();

	zend_class_entry ce_dotnet_ffi;
	INIT_CLASS_ENTRY(ce_dotnet_ffi, "DotnetFFI", dotnet_ffi_funcs_entries);
	dotnet_ffi_entry_ce = zend_register_internal_class_ex(&ce_dotnet_ffi, NULL);

	return SUCCESS;
}
/* }}} */




/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(dotnet_ffi)
{
	/* uncomment this line if you have INI entries */
	UNREGISTER_INI_ENTRIES();
	
	int hr = DestructVm();
	if(hr<0){
		DOTNET_FFI_ERRLOG("DestructVm erro: %d",hr);
		return FAILURE;
	}
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(dotnet_ffi)
{
#if defined(COMPILE_DL_DOTNET_FFI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(dotnet_ffi)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(dotnet_ffi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "dotnet_ffi support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini */
	DISPLAY_INI_ENTRIES();
	
}
/* }}} */


/* {{{ dotnet_ffi_functions[]
 *
 * Every user visible function must have an entry in dotnet_ffi_functions[].
 */
const zend_function_entry dotnet_ffi_functions[] = {
	PHP_FE_END	/* Must be the last line in dotnet_ffi_functions[] */
};
/* }}} */

/* {{{ dotnet_ffi_module_entry
 */
zend_module_entry dotnet_ffi_module_entry = {
	STANDARD_MODULE_HEADER,
	"dotnet_ffi",
	dotnet_ffi_functions,
	PHP_MINIT(dotnet_ffi),
	PHP_MSHUTDOWN(dotnet_ffi),
	PHP_RINIT(dotnet_ffi),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(dotnet_ffi),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(dotnet_ffi),
	PHP_DOTNET_FFI_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DOTNET_FFI
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(dotnet_ffi)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
