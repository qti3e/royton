#include "binding.h"
#include <stdio.h>
#include <errno.h>
#include "_cgo_export.h"

// PHP includes.
#include <main/php.h>
#include <main/SAPI.h>
#include <main/php_main.h>
#include <main/php_variables.h>
#include <TSRM/TSRM.h>

static char royton_ini_defaults[] =
"html_errors = 0\n"
"register_argc_argv = 1\n"
"implicit_flush = 1\n"
"output_buffering = 0\n"
"max_execution_time = 0\n"
"max_input_time = -1\n\0"
;

zend_fcall_info msg_handler_ci;
zend_fcall_info_cache msg_handler_ci_cache;

// Called from PHP, set message handler
PHP_FUNCTION(royton_recv) {
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_FUNC(msg_handler_ci, msg_handler_ci_cache)
  ZEND_PARSE_PARAMETERS_END();
}

// Called from PHP, send data to Go
PHP_FUNCTION(royton_send) {
  char *data;
  size_t nr;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(data, nr)
  ZEND_PARSE_PARAMETERS_END();
  royton_recvCb(data, nr);
  // TODO return value from Go to PHP
}

// Called from Go, send data to PHP
void royton_send(char *data) {
  zval retval;

  zend_string *zs;
  zval str;

  zs = zend_string_init(data, strlen(data), 0);
  ZVAL_STR(&str, zs);

  msg_handler_ci.retval = &retval;
  msg_handler_ci.params = &str;
  msg_handler_ci.param_count = 1;
  zend_call_function(&msg_handler_ci, &msg_handler_ci_cache);
  // TODO return retval to golang.
}

static const zend_function_entry royton_functions[] = {
  ZEND_FE(royton_recv, NULL)
  ZEND_FE(royton_send, NULL)
  {NULL, NULL, NULL}
};


static size_t royton_ub_write(const char *str, size_t str_length)  {
  printf("%s", str);
  return str_length;
}

static void royton_send_header(sapi_header_struct *sapi_header, void *server_context TSRMLS_DC) {
  // Do nothing.
}

sapi_module_struct royton_module = {
  "royton",                    // Name
  "Evented I/O for PHP",       // Pretty Name

  NULL,                        // Startup
  php_module_shutdown_wrapper, // Shutdown

  NULL,                        // Activate
  NULL,                        // Deactivate

  royton_ub_write,             // Unbuffered Write
  NULL,                        // Flush
  NULL,                        // Get UID
  NULL,                        // Getenv

  php_error,                   // Error Handler

  NULL,                        // Header Handler
  NULL,                        // Send Headers Handler
  royton_send_header,          // Send Header Handler

  NULL,                        // Read POST Data
  NULL,                        // Read Cookies

  NULL,                        // Register Server Variables
  NULL,                        // Log Message
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

  royton_ini_defaults,         // INI Entries
  royton_functions,            // Additional Functions
  NULL                         // Input Filter Init
};

void royton_init(void) {
  // Initialize engine
#ifdef HAVE_SIGNAL_H
#if defined(SIGPIPE) && defined(SIG_IGN)
  signal(SIGPIPE, SIG_IGN);
#endif
#endif

  sapi_startup(&royton_module);

  if (php_module_startup(&royton_module, NULL, 0) == FAILURE) {
    sapi_shutdown();
    return;
  }

  // Initialize request lifecycle.
  if (php_request_startup(TSRMLS_C) == FAILURE) {
    return;
  }
}

void royton_eval(char *source) {
  zend_first_try {
    if (zend_eval_string(source, NULL, "" TSRMLS_CC) != SUCCESS) {
      // TODO Print a more useful error message.
      fprintf(stderr, "Error occurred while evaluating code.\n");
      fprintf(stderr, "Code: %s\n", source);
    }
  } zend_end_try();
}
