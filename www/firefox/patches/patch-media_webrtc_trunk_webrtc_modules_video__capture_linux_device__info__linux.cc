$NetBSD: patch-media_webrtc_trunk_webrtc_modules_video__capture_linux_device__info__linux.cc,v 1.12 2017/04/27 01:49:47 ryoon Exp $

--- media/webrtc/trunk/webrtc/modules/video_capture/linux/device_info_linux.cc.orig	2017-04-11 04:15:17.000000000 +0000
+++ media/webrtc/trunk/webrtc/modules/video_capture/linux/device_info_linux.cc
@@ -25,6 +25,9 @@
 #else
 #include <linux/videodev2.h>
 #endif
+#ifdef HAVE_LIBV4L2
+#include <libv4l2.h>
+#endif
 
 #include "webrtc/system_wrappers/include/ref_count.h"
 #include "webrtc/system_wrappers/include/trace.h"
@@ -34,6 +37,15 @@
 #define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
 #endif
 
+#ifdef HAVE_LIBV4L2
+#define open	v4l2_open
+#define close	v4l2_close
+#define dup	v4l2_dup
+#define ioctl	v4l2_ioctl
+#define mmap	v4l2_mmap
+#define munmap	v4l2_munmap
+#endif
+
 namespace webrtc
 {
 namespace videocapturemodule
@@ -274,6 +286,11 @@ int32_t DeviceInfoLinux::GetDeviceName(
     memset(deviceNameUTF8, 0, deviceNameLength);
     memcpy(cameraName, cap.card, sizeof(cap.card));
 
+    if (cameraName[0] == '\0')
+    {
+        sprintf(cameraName, "Camera at /dev/video%d", deviceNumber);
+    }
+
     if (deviceNameLength >= strlen(cameraName))
     {
         memcpy(deviceNameUTF8, cameraName, strlen(cameraName));
