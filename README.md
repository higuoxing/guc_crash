# An extension that makes PostgreSQL (as of fe705ef6fc1d1b4b48aea94a1dd2835a6630dacf) crash

## Steps to reproduce

```bash
# Install the extension
make PG_CONFIG=/<PATH>/<TO>/pg_config install

# Add guc_crash to shared_preload_libraries
# shared_preload_libraries = 'guc_crash'

# Restart the server and execute the following queries.

EXPLAIN (SETTINGS ON) SELECT 1; -- OK
SET crash.str_guc TO 'abc';
EXPLAIN (SETTINGS ON) SELECT 1; -- Server crash
```

## Backtrace

```
#0  0x00007fa6cad88836 in ?? () from /usr/lib/libc.so.6
#1  0x0000558b877b65c0 in get_explain_guc_options ()
#2  0x0000558b8747bdaa in ExplainPrintPlan ()
#3  0x0000558b8747c52d in ExplainOnePlan ()
#4  0x0000558b8747c9df in ExplainOneQuery ()
#5  0x0000558b8747cfda in ExplainQuery ()
#6  0x0000558b87674914 in standard_ProcessUtility ()
#7  0x0000558b87672d5f in PortalRunUtility ()
#8  0x0000558b87673117 in FillPortalStore ()
#9  0x0000558b8767340d in PortalRun ()
#10 0x0000558b8766f7dc in exec_simple_query ()
#11 0x0000558b87671b39 in PostgresMain ()
#12 0x0000558b875ebf5d in ServerLoop.isra.0 ()
#13 0x0000558b875ecf20 in PostmasterMain ()
#14 0x0000558b873433ba in main ()
```
