#include "postgres.h"

#include "fmgr.h"
#include "utils/guc.h"

PG_MODULE_MAGIC;

void _PG_init(void);
char *str_guc;

void _PG_init(void) {
  DefineCustomStringVariable("crash.str_guc", "Some string GUC parameter", NULL,
                             &str_guc, NULL, PGC_USERSET, GUC_GPDB_NEED_SYNC,
                             /*check_hook=*/NULL,
                             /*assign_hook=*/NULL,
                             /*show_hook=*/NULL);
}
