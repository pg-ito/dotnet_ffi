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


/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("dotnet_ffi.libcoreclr_file_path",      "/mnt/d/proj/dotnet_invoke/php-src72/php-src-php-7.2.24/ext/dotnet_ffi/dotnet_dll/publish/libcoreclr.so", PHP_INI_SYSTEM, OnUpdateString, libcoreclr_file_path, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_project_name",      "invokee_test, Version=1.0.0.0", PHP_INI_SYSTEM, OnUpdateString, target_project_name, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_class_name",      "invokee_test.InvokeeTest", PHP_INI_SYSTEM, OnUpdateString, target_class_name, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_method_invoke_ret_str_arg_str",     "InvokeReturnString", PHP_INI_SYSTEM, OnUpdateString, target_method_invoke_ret_str_arg_str, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_method_invoke_ret_s64_arg_s64",     "return_s64_arg_s64", PHP_INI_SYSTEM, OnUpdateString, target_method_invoke_ret_s64_arg_s64, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.target_method_invoke_ret_dbl_arg_dbl",     "return_double_arg_double", PHP_INI_SYSTEM, OnUpdateString, target_method_invoke_ret_dbl_arg_dbl, zend_dotnet_ffi_globals, dotnet_ffi_globals)
PHP_INI_END()



PHP_FUNCTION(dotnet_ffi_ret_double_double)
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

PHP_FUNCTION(dotnet_ffi_ret_s64_arg_s64)
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

PHP_METHOD(DotnetFFI, __construct)
{
	zval *timezone_object = NULL;
	char *time_str = NULL;
	size_t time_str_len = 0;
	zend_error_handling error_handling;

	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 0, 2)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(time_str, time_str_len)
	ZEND_PARSE_PARAMETERS_END();

}

PHP_FUNCTION(dotnet_ffi_ret_long_long_long)
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

PHP_FUNCTION(dotnet_ffi_ret_string_string)
{
	char *arg = NULL;
	size_t arg_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	int hr=-1;
	char *retString = emalloc(0);
	int strLen = 0;
	invoke_ret_str_arg_str(&hr, arg, arg_len, &retString, &strLen, INI_STR("dotnet_ffi.target_method_invoke_ret_str_arg_str"));
	if(hr < 0){
		DOTNET_FFI_ERRLOG("invoke_ret_str_arg_str Fail hr: %d\n",hr);
		return;
	}
	
	zend_string *result = strpprintf(0, "%s", retString);
	RETURN_STR(result);
	efree(retString);
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
    PHP_ME(DotnetFFI, __construct, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(DotnetFFI, ret_s64_arg_s64, NULL, ZEND_ACC_PUBLIC)
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

/*
	zend_class_entry ce_dotnet_ffi;
	INIT_CLASS_ENTRY(ce_dotnet_ffi, "DotnetFFI", dotnet_ffi_funcs_entries);
	dotnet_ffi_entry_ce = zend_register_internal_class_ex(&ce_dotnet_ffi, NULL);
*/



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
	PHP_FE(dotnet_ffi_ret_s64_arg_s64,	NULL)
	PHP_FE(dotnet_ffi_ret_double_double,	NULL)
	PHP_FE(dotnet_ffi_ret_long_long_long,	NULL)
	PHP_FE(dotnet_ffi_ret_string_string,	NULL)
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
