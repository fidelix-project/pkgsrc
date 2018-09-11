$NetBSD: patch-src_utils_padsp.c,v 1.2 2018/09/11 16:39:42 jperkin Exp $

ioctl() takes u_long argument on NetBSD.
On NetBSD<6 and 6.99.0-6.99.7, use third parameter in ioctl instead of varargs.
stat() system call has been versioned, use latest version when dlopen()ing.
Try more typical device names.
SOUND_PCM_* is not available on SunOS.

--- src/utils/padsp.c.orig	2018-07-13 19:06:13.000000000 +0000
+++ src/utils/padsp.c
@@ -48,6 +48,10 @@
 #include <linux/sockios.h>
 #endif
 
+#ifdef __NetBSD__
+#include <sys/param.h>
+#endif
+
 #include <pulse/pulseaudio.h>
 #include <pulse/gccmacro.h>
 #include <pulsecore/llist.h>
@@ -115,7 +119,11 @@ static pthread_mutex_t func_mutex = PTHR
 
 static PA_LLIST_HEAD(fd_info, fd_infos) = NULL;
 
+#ifdef __NetBSD__
+static int (*_ioctl)(int, u_long, void *) = NULL;
+#else
 static int (*_ioctl)(int, int, void*) = NULL;
+#endif
 static int (*_close)(int) = NULL;
 static int (*_open)(const char *, int, mode_t) = NULL;
 static int (*___open_2)(const char *, int) = NULL;
@@ -143,6 +151,15 @@ static inline fnptr dlsym_fn(void *handl
     return (fnptr) (long) dlsym(handle, symbol);
 }
 
+#ifdef __NetBSD__
+#define LOAD_IOCTL_FUNC() \
+do { \
+    pthread_mutex_lock(&func_mutex); \
+    if (!_ioctl)  \
+       _ioctl = (int (*)(int, u_long, void*)) dlsym_fn(RTLD_NEXT, "ioctl"); \
+    pthread_mutex_unlock(&func_mutex); \
+} while(0)
+#else
 #define LOAD_IOCTL_FUNC() \
 do { \
     pthread_mutex_lock(&func_mutex); \
@@ -150,6 +167,7 @@ do { \
         _ioctl = (int (*)(int, int, void*)) dlsym_fn(RTLD_NEXT, "ioctl"); \
     pthread_mutex_unlock(&func_mutex); \
 } while(0)
+#endif
 
 #define LOAD_OPEN_FUNC() \
 do { \
@@ -199,11 +217,21 @@ do { \
     pthread_mutex_unlock(&func_mutex); \
 } while(0)
 
+
+#ifdef __NetBSD__
+#if (__NetBSD_Version__ < 600000000)
+#define STAT_FUNC "__stat30"
+#else
+#define STAT_FUNC "__stat50"
+#endif
+#else
+#define STAT_FUNC "stat"
+#endif
 #define LOAD_STAT_FUNC() \
 do { \
     pthread_mutex_lock(&func_mutex); \
     if (!_stat) \
-        _stat = (int (*)(const char *, struct stat *)) dlsym_fn(RTLD_NEXT, "stat"); \
+        _stat = (int (*)(const char *, struct stat *)) dlsym_fn(RTLD_NEXT, STAT_FUNC); \
     pthread_mutex_unlock(&func_mutex); \
 } while(0)
 
@@ -2295,7 +2323,7 @@ static int dsp_ioctl(fd_info *i, unsigne
             break;
         }
 
-#ifdef HAVE_DECL_SOUND_PCM_READ_RATE
+#if HAVE_DECL_SOUND_PCM_READ_RATE
         case SOUND_PCM_READ_RATE:
             debug(DEBUG_LEVEL_NORMAL, __FILE__": SOUND_PCM_READ_RATE\n");
 
@@ -2305,7 +2333,7 @@ static int dsp_ioctl(fd_info *i, unsigne
             break;
 #endif
 
-#ifdef HAVE_DECL_SOUND_PCM_READ_CHANNELS
+#if HAVE_DECL_SOUND_PCM_READ_CHANNELS
         case SOUND_PCM_READ_CHANNELS:
             debug(DEBUG_LEVEL_NORMAL, __FILE__": SOUND_PCM_READ_CHANNELS\n");
 
@@ -2315,7 +2343,7 @@ static int dsp_ioctl(fd_info *i, unsigne
             break;
 #endif
 
-#ifdef HAVE_DECL_SOUND_PCM_READ_BITS
+#if HAVE_DECL_SOUND_PCM_READ_BITS
         case SOUND_PCM_READ_BITS:
             debug(DEBUG_LEVEL_NORMAL, __FILE__": SOUND_PCM_READ_BITS\n");
 
@@ -2394,21 +2422,33 @@ fail:
     return ret;
 }
 
-#ifndef __GLIBC__
+/* NetBSD < 6 and 6.99.0 - 6.99.6 used a different ioctl() definition */
+#if defined(__NetBSD__) && (__NetBSD_Version__ < 600000000 ||  \
+    (__NetBSD_Version__ > 699000000 && __NetBSD_Version__ < 699000700) )
+# define OLD_NETBSD_IOCTL_CALL
+#endif
+
+#if !defined(__GLIBC__) && !defined(__NetBSD__)
 int ioctl(int fd, int request, ...) {
+#elif defined(OLD_NETBSD_IOCTL_CALL)
+int ioctl(int fd, u_long request, void *_argp) {
 #else
 int ioctl(int fd, unsigned long request, ...) {
 #endif
     fd_info *i;
+#if !defined(OLD_NETBSD_IOCTL_CALL)
     va_list args;
+#endif
     void *argp;
     int r, _errno = 0;
 
     debug(DEBUG_LEVEL_VERBOSE, __FILE__": ioctl()\n");
 
+#if defined(OLD_NETBSD_IOCTL_CALL)
     va_start(args, request);
     argp = va_arg(args, void *);
     va_end(args);
+#endif
 
     if (!function_enter()) {
         LOAD_IOCTL_FUNC();
@@ -2536,7 +2576,7 @@ int stat(const char *pathname, struct st
 }
 #ifdef HAVE_OPEN64
 #undef stat64
-#ifdef __GLIBC__
+#if defined(__GLIBC__) || defined(__sun)
 int stat64(const char *pathname, struct stat64 *buf) {
 #else
 int stat64(const char *pathname, struct stat *buf) {
