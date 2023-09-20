# An extension that makes gpdb (as of b15fb5d) crash

## Steps to reproduce

```bash
# Install the extension
make install

# Load this extension as shared preload extension
gpconfig -c shared_preload_libraries -v 'guc_crash'

# Restart the cluster
gpstop -ari
```

## Backtrace

```
#0  addOneOption (option=option@entry=0x7ffcc0c67a58, diff=diff@entry=0x7ffcc0c67a40, guc=guc@entry=0x55fb1a9c3580)
    at cdbgang.c:331
331                                     for (i = 0; str[i] != '\0'; i++)
[Current thread is 1 (Thread 0x7f4b4c77fc00 (LWP 162127))]
(gdb) bt
#0  addOneOption (option=option@entry=0x7ffcc0c67a58, diff=diff@entry=0x7ffcc0c67a40, guc=guc@entry=0x55fb1a9c3580)
    at cdbgang.c:331
#1  0x000055fb1334611e in makeOptions (options=options@entry=0x7ffcc0c67b48, diff_options=diff_options@entry=0x7ffcc0c67b58)
    at cdbgang.c:440
#2  0x000055fb13347986 in cdbgang_createGang_async (segments=<optimized out>, segmentType=<optimized out>)
    at cdbgang_async.c:163
#3  0x000055fb1334597f in cdbgang_createGang (segments=0x3d, segments@entry=0x55fb1ab09a90, segmentType=3234232400)
    at cdbgang.c:97
#4  0x000055fb13345a4a in AllocateGang (ds=ds@entry=0x55fb1ab761d8, type=type@entry=GANGTYPE_PRIMARY_WRITER,
    segments=segments@entry=0x55fb1ab09a90) at cdbgang.c:134
#5  0x000055fb13344cbf in cdbdisp_dispatchCommandInternal (pQueryParms=0x55fb1ab09b18, flags=flags@entry=0,
    segments=segments@entry=0x55fb1ab09a90, cdb_pgresults=cdb_pgresults@entry=0x7ffcc0c67dd0) at cdbdisp_query.c:489
#6  0x000055fb13344c4e in CdbDispatchCommandToSegments (
    strCommand=strCommand@entry=0x55fb138985ff "select * from gp_terminate_mpp_backends()", flags=flags@entry=0,
    segments=0x55fb1ab09a90, cdb_pgresults=cdb_pgresults@entry=0x7ffcc0c67dd0) at cdbdisp_query.c:404
#7  0x000055fb13344ba1 in CdbDispatchCommand (strCommand=0x55fb138985ff "select * from gp_terminate_mpp_backends()",
    flags=flags@entry=0, cdb_pgresults=cdb_pgresults@entry=0x7ffcc0c67dd0) at cdbdisp_query.c:376
#8  0x000055fb133784ac in TerminateMppBackends () at cdbdtxrecovery.c:265
#9  0x000055fb133782d3 in recoverTM () at cdbdtxrecovery.c:153
#10 0x000055fb13377ff4 in DtxRecoveryMain (main_arg=<optimized out>) at cdbdtxrecovery.c:697
#11 0x000055fb130d8aee in StartBackgroundWorker () at bgworker.c:955
#12 0x000055fb130eba4b in do_start_bgworker (rw=rw@entry=0x55fb1a9c11c0) at postmaster.c:6450
#13 0x000055fb130e7a24 in maybe_start_bgworkers () at postmaster.c:6706
#14 0x000055fb130e6d6d in reaper (postgres_signal_arg=<optimized out>) at postmaster.c:3513
#15 <signal handler called>
#16 0x00007f4b4c90e744 in select () from /usr/lib/libc.so.6
#17 0x000055fb130e7bc5 in ServerLoop () at postmaster.c:1963
#18 0x000055fb130e5f43 in PostmasterMain (argc=argc@entry=5, argv=argv@entry=0x55fb1a994e30) at postmaster.c:1633
#19 0x000055fb13005055 in main (argc=5, argv=0x55fb1a994e30) at main.c:240
```
