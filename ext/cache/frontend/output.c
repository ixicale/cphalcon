
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2012 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  +------------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_phalcon.h"
#include "phalcon.h"

#include "Zend/zend_operators.h"
#include "Zend/zend_exceptions.h"
#include "Zend/zend_interfaces.h"

#include "kernel/main.h"
#include "kernel/memory.h"

#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/fcall.h"

/**
 * Phalcon\Cache\Frontend\Output
 *
 * Allows to cache output fragments captured with ob_* functions
 *
 */


/**
 * Phalcon\Cache\Frontend\Output constructor
 *
 * @param array $frontendOptions
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, __construct){

	zval *frontend_options = NULL;
	zval *a0 = NULL;

	PHALCON_MM_GROW();

	
	PHALCON_INIT_VAR(a0);
	array_init(a0);
	zend_update_property(phalcon_cache_frontend_output_ce, this_ptr, SL("_frontendOptions"), a0 TSRMLS_CC);
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &frontend_options) == FAILURE) {
		PHALCON_MM_RESTORE();
		RETURN_NULL();
	}

	if (!frontend_options) {
		PHALCON_INIT_NVAR(frontend_options);
		array_init(frontend_options);
	}
	
	phalcon_update_property_zval(this_ptr, SL("_frontendOptions"), frontend_options TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns cache lifetime
 *
 * @return integer
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, getLifetime){

	zval *options, *lifetime;
	int eval_int;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(options);
	phalcon_read_property(&options, this_ptr, SL("_frontendOptions"), PH_NOISY_CC);
	eval_int = phalcon_array_isset_string(options, SS("lifetime"));
	if (eval_int) {
		PHALCON_INIT_VAR(lifetime);
		phalcon_array_fetch_string(&lifetime, options, SL("lifetime"), PH_NOISY_CC);
		
		RETURN_CCTOR(lifetime);
	}
	
	PHALCON_MM_RESTORE();
	RETURN_LONG(1);
}

/**
 * Check whether if frontend is buffering output
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, isBuffering){

	zval *buffering;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(buffering);
	phalcon_read_property(&buffering, this_ptr, SL("_buffering"), PH_NOISY_CC);
	
	RETURN_CCTOR(buffering);
}

/**
 * Starts output frontend
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, start){


	PHALCON_MM_GROW();

	phalcon_update_property_bool(this_ptr, SL("_buffering"), 1 TSRMLS_CC);
	PHALCON_CALL_FUNC_NORETURN("ob_start");
	
	PHALCON_MM_RESTORE();
}

/**
 * Returns output cached content
 *
 * @return string
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, getContent){

	zval *buffering, *contents;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(buffering);
	phalcon_read_property(&buffering, this_ptr, SL("_buffering"), PH_NOISY_CC);
	if (zend_is_true(buffering)) {
		PHALCON_INIT_VAR(contents);
		PHALCON_CALL_FUNC(contents, "ob_get_contents");
		
		RETURN_CCTOR(contents);
	}
	
	PHALCON_MM_RESTORE();
	RETURN_NULL();
}

/**
 * Stops output frontend
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, stop){

	zval *buffering;

	PHALCON_MM_GROW();

	PHALCON_INIT_VAR(buffering);
	phalcon_read_property(&buffering, this_ptr, SL("_buffering"), PH_NOISY_CC);
	if (zend_is_true(buffering)) {
		PHALCON_CALL_FUNC_NORETURN("ob_end_clean");
	}
	
	phalcon_update_property_bool(this_ptr, SL("_buffering"), 0 TSRMLS_CC);
	
	PHALCON_MM_RESTORE();
}

/**
 * Prepare data to be stored
 *
 * @param mixed $data
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, beforeStore){

	zval *data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data) == FAILURE) {
		RETURN_NULL();
	}

	
	RETURN_CCTORW(data);
}

/**
 * Prepares data to be retrieved to user
 *
 * @param mixed $data
 */
PHP_METHOD(Phalcon_Cache_Frontend_Output, afterRetrieve){

	zval *data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data) == FAILURE) {
		RETURN_NULL();
	}

	
	RETURN_CCTORW(data);
}

