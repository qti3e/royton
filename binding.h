#ifndef ENGINE_H
#define ENGINE_H

#define return_multi(value, error) errno = error; return value

typedef struct _php_engine {
#ifdef ZTS
  void ***tsrm_ls; // Local storage for thread-safe operations, used across the PHP engine.
#endif
} php_engine;

typedef struct _engine_context {
  php_engine *engine; // Parent engine instance.
  void *parent;       // Pointer to parent Go context, used for passing to callbacks.
} engine_context;

void asyncphp_init(void);

#endif
