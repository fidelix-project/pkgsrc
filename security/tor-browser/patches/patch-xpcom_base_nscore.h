$NetBSD: patch-xpcom_base_nscore.h,v 1.3 2019/02/25 15:32:24 wiz Exp $

* Support llvm/clang

--- xpcom/base/nscore.h.orig	2019-02-23 20:01:00.000000000 +0000
+++ xpcom/base/nscore.h
@@ -76,7 +76,7 @@
  *           NS_HIDDEN_(int) NS_FASTCALL func2(char *foo);
  */
 
-#if defined(__i386__) && defined(__GNUC__)
+#if defined(__i386__) && defined(__GNUC__) && !(defined(__clang__) && __clang_major__ == 3 && __clang_minor__ == 4 && __clang_patchlevel__ == 0)
 #define NS_FASTCALL __attribute__((regparm(3), stdcall))
 #define NS_CONSTRUCTOR_FASTCALL __attribute__((regparm(3), stdcall))
 #elif defined(XP_WIN) && !defined(_WIN64)
