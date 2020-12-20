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


#define DOTNET_FFI_ERRLOG( fmt, ... ) \
  printf( "DOTNET_FFI_ERR %s File:%s:%d Func:%s Log:%s\n", fmt, __FILE__, __LINE__, __func__, __VA_ARGS__ )


/* If you declare any globals in php_dotnet_ffi.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(dotnet_ffi)
*/

/* True global resources - no need for thread safety here */
static int le_dotnet_ffi;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("dotnet_ffi.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_dotnet_ffi_globals, dotnet_ffi_globals)
    STD_PHP_INI_ENTRY("dotnet_ffi.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_dotnet_ffi_globals, dotnet_ffi_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_dotnet_ffi_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_dotnet_ffi_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	// int retEx = ExternTest(5);
	// printf("retEx %d\n",retEx);
	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "dotnet_ffi", arg);

	RETURN_STR(strg);
}
PHP_FUNCTION(dotnet_ffi_ret_double_double)
{
	double *arg = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &arg) == FAILURE) {
		return;
	}
	int hr=-1;
	double res = InvokeReturnDouble(&hr, *arg);
	if(hr < 0){
		DOTNET_FFI_ERRLOG("InvokeReturnDouble Fail hr: %d",hr);
		return;
	}
	RETURN_DOUBLE(res);
}

PHP_FUNCTION(dotnet_ffi_ret_long_long_long)
{
	zend_long *arg1 = NULL;
	zend_long *arg2 = NULL;


	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &arg1, &arg2) == FAILURE) {
		return;
	}
	int hr=-1;
	zend_long result = InvokeReturnInt64(&hr, *arg1, *arg2);
	if(hr < 0){
		DOTNET_FFI_ERRLOG("InvokeReturnInt64 Fail hr: %d",hr);
		return;
	}
	RETURN_LONG(result);
}

PHP_FUNCTION(dotnet_ffi_ret_string_string)
{
	char *arg = NULL;
	size_t arg_len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	int hr=-1;

	char *retString = NULL;
	int strLen =0;
	InvokeReturnString(&hr, arg, arg_len, &retString, &strLen);
	if(hr < 0){
		DOTNET_FFI_ERRLOG("InvokeReturnString Fail hr: %d",hr);
		return;
	}
	zend_string *result =  zend_string_init(*retString, strLen, 0);

	free(retString);
	RETURN_STR(result);
	zend_string_release(result);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_dotnet_ffi_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_dotnet_ffi_init_globals(zend_dotnet_ffi_globals *dotnet_ffi_globals)
{
	dotnet_ffi_globals->global_value = 0;
	dotnet_ffi_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(dotnet_ffi)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	// @TODO load ini settings
	int hr = LoadClr("/mnt/d/proj/dotnet_invoke/php-src72/php-src-php-7.2.24/ext/dotnet_ffi/dotnet_dll/publish/libcoreclr.so");
	if(hr<0){
		DOTNET_FFI_ERRLOG("LoadClr erro: %d",hr);
	}
	hr = InitClr();
	if(hr<0){
		DOTNET_FFI_ERRLOG("InitClr erro: %d", hr);
	}
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(dotnet_ffi)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	int hr = DestructVm();
	if(hr<0){
		DOTNET_FFI_ERRLOG("DestructVm erro: %d",hr);
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

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ dotnet_ffi_functions[]
 *
 * Every user visible function must have an entry in dotnet_ffi_functions[].
 */
const zend_function_entry dotnet_ffi_functions[] = {
	PHP_FE(confirm_dotnet_ffi_compiled,	NULL)		/* For testing, remove later. */
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
