#include "binding.h"
#include <stdio.h>
#include <errno.h>

// PHP includes.
#include <main/php.h>
#include <main/SAPI.h>
#include <main/php_main.h>
#include <main/php_variables.h>
#include <TSRM/TSRM.h>

const char engine_ini_defaults[] =
"html_errors = 0\n"
"register_argc_argv = 1\n"
"implicit_flush = 1\n"
"output_buffering = 0\n"
"max_execution_time = 0\n"
"max_input_time = -1\n\0"
;

static int engine_ub_write(const char *str, uint str_length TSRMLS_DC)  {
  printf(str);
  return str_length;
}

static void engine_send_header(sapi_header_struct *sapi_header, void *server_context TSRMLS_DC) {
  // Do nothing.
}

static char *engine_read_cookies(TSRMLS_D) {
  return NULL;
}

static void engine_register_variables(zval *track_vars_array TSRMLS_DC) {
  php_import_environment_variables(track_vars_array TSRMLS_CC);
}

static void engine_log_message(char *message TSRMLS_C) {
  // Nothing.
}

sapi_module_struct engine_module = {
  "async-php",                 // Name
  "Asynchronous PHP runtime",  // Pretty Name

  NULL,                        // Startup
  php_module_shutdown_wrapper, // Shutdown

  NULL,                        // Activate
  NULL,                        // Deactivate

  engine_ub_write,             // Unbuffered Write
  NULL,                        // Flush
  NULL,                        // Get UID
  NULL,                        // Getenv

  php_error,                   // Error Handler

  NULL,                        // Header Handler
  NULL,                        // Send Headers Handler
  engine_send_header,          // Send Header Handler

  NULL,                        // Read POST Data
  engine_read_cookies,         // Read Cookies

  engine_register_variables,   // Register Server Variables
  engine_log_message,          // Log Message
  NULL,                        // Get Request Time

  STANDARD_SAPI_MODULE_PROPERTIES
};

void asyncphp_init(void) {
  // Initialize engine
#ifdef HAVE_SIGNAL_H
#if defined(SIGPIPE) && defined(SIG_IGN)
  signal(SIGPIPE, SIG_IGN);
#endif
#endif

  sapi_startup(&engine_module);

  engine_module.ini_entries = malloc(sizeof(engine_ini_defaults));
  memcpy(engine_module.ini_entries, engine_ini_defaults, sizeof(engine_ini_defaults));

  if (php_module_startup(&engine_module, NULL, 0) == FAILURE) {
    sapi_shutdown();
    return;
  }

  // Initialize request lifecycle.
  if (php_request_startup(TSRMLS_C) == FAILURE) {
    return;
  }

  // Attempt to evaluate inline script.
  zend_first_try {
    zend_eval_string("$a = 4; echo $a . \"\\n\";", NULL, "" TSRMLS_CC);
    zend_eval_string("$a++; echo $a . \"\\n\";", NULL, "" TSRMLS_CC);
    printf("Executed script.\n");
  } zend_end_try();
}
