$NetBSD: patch-devrplay_devrplay.c,v 1.2 2018/02/20 08:35:52 dholland Exp $

Fix Linux build.

--- devrplay/devrplay.c.orig	1999-03-21 00:44:48.000000000 +0000
+++ devrplay/devrplay.c
@@ -26,6 +26,8 @@
  * Copyright (C) 1998, 1999 Manish Singh <yosh@gimp.org>
  */
 
+#define _GNU_SOURCE 1
+
 #ifdef HAVE_CONFIG_H
 #include "config.h"
 #endif
