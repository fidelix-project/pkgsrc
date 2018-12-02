$NetBSD: patch-builtin-date.c,v 1.2 2018/12/02 06:49:24 wiz Exp $

Fix missing tm_zone on SunOS.
Pull in upstream fix for missing timelocal().

--- builtin-date.c.orig	2018-09-24 21:43:45.000000000 +0000
+++ builtin-date.c
@@ -76,7 +76,11 @@ to_date(struct tm *tm)
     BoxValueSet (box, 6, int_value(tm->tm_wday));
     BoxValueSet (box, 7, int_value(tm->tm_yday));
     BoxValueSet (box, 8, tm->tm_isdst ? TrueVal : FalseVal);
+#ifdef __sun
+    BoxValueSet (box, 9, NewStrString("GMT"));
+#else
     BoxValueSet (box, 9, NewStrString(tm->tm_zone));
+#endif
     return ret;
 }
 
@@ -92,7 +96,9 @@ from_date(Value date, struct tm *tm)
     tm->tm_wday = value_int(date, "wday", "invalid wday", 0);
     tm->tm_yday = value_int(date, "yday", "invalid yday", 0);
     tm->tm_isdst = value_bool(date, "isdst", "invalid isdst", 0);
+#ifndef __sun
     tm->tm_zone = NULL;
+#endif
 }
 
 static Value
