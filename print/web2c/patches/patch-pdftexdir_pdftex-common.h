$NetBSD: patch-pdftexdir_pdftex-common.h,v 1.2 2019/05/14 13:23:10 adam Exp $

Fix buildling.

--- pdftexdir/pdftex-common.h.orig	2016-11-25 18:24:37.000000000 +0000
+++ pdftexdir/pdftex-common.h
@@ -101,7 +101,7 @@ extern void tex_printf(const char *, ...
 extern void write_epdf(void);
 
 /* writeenc.c */
-extern void epdf_write_enc(char **, int);
+extern void epdf_write_enc(const char **, int);
 
 /* writeimg.c */
 extern float epdf_width;
