$NetBSD: patch-tools_strutil.h,v 1.1 2012/12/17 03:37:20 dholland Exp $

add <cstring> for strcasecmp.

--- tools/strutil.h~	2006-12-27 11:04:05.000000000 +0000
+++ tools/strutil.h
@@ -23,6 +23,7 @@ This is part of a toolkit used to assist
 #define STRUTIL_H
 
 #include <string>
+#include <cstring>
 #include <vector>
 #include <cctype>
 
