$NetBSD: patch-openbsd-compat_openbsd-compat.h,v 1.3 2015/07/09 16:14:23 taca Exp $

strtoll() declaration

--- openbsd-compat/openbsd-compat.h.orig	2015-07-01 02:35:31.000000000 +0000
+++ openbsd-compat/openbsd-compat.h
@@ -91,6 +91,10 @@ size_t strlcat(char *dst, const char *sr
 int setenv(register const char *name, register const char *value, int rewrite);
 #endif
 
+#ifndef HAVE_STRTOLL
+long long strtoll(const char *, char **, int);
+#endif
+
 #ifndef HAVE_STRMODE
 void strmode(int mode, char *p);
 #endif
