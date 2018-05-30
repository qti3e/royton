#include "timers.h"
#include "_cgo_export.h"

// PHP includes.
#include <main/php.h>
#include <main/SAPI.h>
#include <main/php_main.h>
#include <main/php_variables.h>

PHP_FUNCTION(setTimeout) {
  double f;

  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_DOUBLE(f);
  ZEND_PARSE_PARAMETERS_END();

  double id = SetTimeout(f);

  RETURN_DOUBLE(id);
}
