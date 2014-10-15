$NetBSD: patch-ipc_chromium_src_base_process__util.h,v 1.5 2014/10/15 13:07:07 ryoon Exp $

--- ipc/chromium/src/base/process_util.h.orig	2014-10-11 09:06:28.000000000 +0000
+++ ipc/chromium/src/base/process_util.h
@@ -13,7 +13,7 @@
 #if defined(OS_WIN)
 #include <windows.h>
 #include <tlhelp32.h>
-#elif defined(OS_LINUX) || defined(__GLIBC__)
+#elif defined(OS_LINUX) || defined(__GLIBC__) || defined(OS_SOLARIS)
 #include <dirent.h>
 #include <limits.h>
 #include <sys/types.h>
@@ -32,6 +32,9 @@
 typedef PROCESSENTRY32 ProcessEntry;
 typedef IO_COUNTERS IoCounters;
 #elif defined(OS_POSIX)
+#ifndef NAME_MAX
+#define NAME_MAX _POSIX_NAME_MAX
+#endif
 // TODO(port): we should not rely on a Win32 structure.
 struct ProcessEntry {
   int pid;
