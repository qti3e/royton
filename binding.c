#include "binding.h"
#include <stdio.h>
#include <errno.h>

// PHP includes.
#include <main/php.h>
#include <main/SAPI.h>
#include <main/php_main.h>
#include <main/php_variables.h>
#include <TSRM/TSRM.h>

static char engine_ini_defaults[] =
"html_errors = 0\n"
"register_argc_argv = 1\n"
"implicit_flush = 1\n"
"output_buffering = 0\n"
"max_execution_time = 0\n"
"max_input_time = -1\n\0"
;

PHP_FUNCTION(async_test){
  printf("From C\n");
}

static const zend_function_entry async_functions[] = {
  ZEND_FE(async_test, NULL)
  {NULL, NULL, NULL}
};


static size_t engine_ub_write(const char *str, size_t str_length)  {
  printf("%s", str);
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

static void engine_log_message(char *message, int syslog_type_int) {
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
  NULL,                        // Terminate process

  NULL,                        // PHP INI Path Override

  NULL,                        // Default POST Reader
  NULL,                        // Treat Data
  NULL,                        // Executable Location

  0,                           // PHP INI Ignore
  0,                           // PHP INI Ignore CWD

  NULL,                        // Get FD
  NULL,                        // Force HTTP 10

  NULL,                        // Get Target UID
  NULL,                        // Get Target GID

  NULL,                        // Input Filter

  NULL,                        // INI Defaults
  0,                           // PHPInfo as Text

  engine_ini_defaults,         // INI Entries
  async_functions,             // Additional Functions
  NULL                         // Input Filter Init
};

void asyncphp_init(void) {
  // Initialize engine
#ifdef HAVE_SIGNAL_H
#if defined(SIGPIPE) && defined(SIG_IGN)
  signal(SIGPIPE, SIG_IGN);
#endif
#endif

  sapi_startup(&engine_module);

  if (php_module_startup(&engine_module, NULL, 0) == FAILURE) {
    sapi_shutdown();
    return;
  }

  // Initialize request lifecycle.
  if (php_request_startup(TSRMLS_C) == FAILURE) {
    return;
  }
}

void asyncphp_eval(char *source) {
  zend_first_try {
    if (zend_eval_string(source, NULL, "" TSRMLS_CC) != SUCCESS) {
      // TODO Print a more useful error message.
      fprintf(stderr, "Error occurred while evaluating code.\n");
      fprintf(stderr, "Code: %s\n", source);
    }
  } zend_end_try();
}
