MODULES = guc_crash
EXTENSION = guc_crash
DATA = guc_crash--1.0.0.sql
PG_CONFIG := pg_config

PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
