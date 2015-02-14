$NetBSD: patch-netwerk_base_public_nsNetUtil.h,v 1.1 2015/02/14 07:59:24 martin Exp $

https://bugzilla.mozilla.org/show_bug.cgi?id=1130822
Fix obivous alignment issues (causing crashes on some architectures).

--- netwerk/base/public/nsNetUtil.h.orig	2015-01-23 07:00:06.000000000 +0100
+++ netwerk/base/public/nsNetUtil.h	2015-02-13 08:51:18.000000000 +0100
@@ -13,6 +13,7 @@
 #include "nsMemory.h"
 #include "nsCOMPtr.h"
 #include "prio.h" // for read/write flags, permissions, etc.
+#include "prnetdb.h"
 #include "nsHashKeys.h"
 
 #include "plstr.h"
@@ -2717,6 +2718,26 @@
 bool NS_IsReasonableHTTPHeaderValue(const nsACString& aValue);
 
 /**
+ * Return a host endian value decoded from network byte order,
+ * accessed in an alignement safe way.
+ */
+inline uint16_t NS_decodeN16(const void *bytes)
+{
+    uint16_t tmp;
+
+    memcpy(&tmp, bytes, sizeof tmp);
+    return PR_ntohs(tmp);
+}
+
+inline uint32_t NS_decodeN32(const void *bytes)
+{
+    uint32_t tmp;
+
+    memcpy(&tmp, bytes, sizeof tmp);
+    return PR_ntohl(tmp);
+}
+
+/**
  * Return true if the given string is a valid HTTP token per RFC 2616 section
  * 2.2.
  */
