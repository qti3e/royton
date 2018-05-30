#include "timers.h"
#include "_cgo_export.h"
#include "stdio.h"

// PHP includes.
#include <main/php.h>
#include <main/SAPI.h>
#include <main/php_main.h>
#include <main/php_variables.h>

int nextTimerId = 0;
zend_fcall_info fci[20];
zend_fcall_info_cache fcc[20];

PHP_FUNCTION(setTimeout) {
  int id = nextTimerId++;
  double delay;

  ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_FUNC(fci[id], fcc[id])
    Z_PARAM_DOUBLE(delay);
  ZEND_PARSE_PARAMETERS_END();

  SetTimeout(id, delay);

  RETURN_DOUBLE(id);
}

void SetTimeoutCb(int id) {
  printf("R; %d\n", id);
  zval retval;
  fci[id].retval = &retval;
  zend_call_function(&fci[id], &fcc[id]);
}
