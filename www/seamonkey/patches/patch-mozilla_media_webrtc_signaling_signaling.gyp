$NetBSD: patch-mozilla_media_webrtc_signaling_signaling.gyp,v 1.1 2013/05/23 13:25:30 ryoon Exp $

--- mozilla/media/webrtc/signaling/signaling.gyp.orig	2013-05-03 03:08:06.000000000 +0000
+++ mozilla/media/webrtc/signaling/signaling.gyp
@@ -217,6 +217,19 @@
           'cflags_mozilla': [
           ],
         }],
+        ['os_bsd==1', {
+          'include_dirs': [
+          ],
+          'defines': [
+            # avoiding pointless ifdef churn
+            'SIP_OS_OSX',
+            'OSX',
+            'SECLIB_OPENSSL',
+          ],
+
+          'cflags_mozilla': [
+          ],
+        }],
         ['OS=="mac"', {
           'include_dirs': [
           ],
@@ -752,7 +765,7 @@
           ],
 
         }],
-        ['OS=="mac"', {
+        ['OS=="mac" or os_bsd==1', {
 
           'include_dirs': [
           ],
@@ -797,14 +810,13 @@
 
           'defines' : [
             'SIP_OS_OSX',
-            '_POSIX_SOURCE',
+            # using BSD extensions, leave _POSIX_SOURCE undefined
             'CPR_MEMORY_LITTLE_ENDIAN',
             'NO_SOCKET_POLLING',
             'USE_TIMER_SELECT_BASED',
             'FULL_BUILD',
             'STUBBED_OUT',
             'USE_PRINTF',
-            '_DARWIN_C_SOURCE',
             'NO_NSPR_10_SUPPORT',
           ],
 
