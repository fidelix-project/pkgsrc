$NetBSD: patch-gio_gcredentialsprivate.h,v 1.3 2018/10/19 16:44:15 leot Exp $

NetBSD has G_CREDENTIALS_SOCKET_GET_CREDENTIALS_SUPPORTED.

--- gio/gcredentialsprivate.h.orig	2017-07-13 23:03:38.000000000 +0000
+++ gio/gcredentialsprivate.h
@@ -47,7 +47,7 @@
 #define G_CREDENTIALS_USE_NETBSD_UNPCBID 1
 #define G_CREDENTIALS_NATIVE_TYPE G_CREDENTIALS_TYPE_NETBSD_UNPCBID
 #define G_CREDENTIALS_NATIVE_SIZE (sizeof (struct unpcbid))
-/* #undef G_CREDENTIALS_UNIX_CREDENTIALS_MESSAGE_SUPPORTED */
+#define G_CREDENTIALS_SOCKET_GET_CREDENTIALS_SUPPORTED 1
 #define G_CREDENTIALS_SPOOFING_SUPPORTED 1
 
 #elif defined(__OpenBSD__)
