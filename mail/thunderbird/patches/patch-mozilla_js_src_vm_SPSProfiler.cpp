$NetBSD: patch-mozilla_js_src_vm_SPSProfiler.cpp,v 1.3 2016/04/17 18:33:50 ryoon Exp $

--- mozilla/js/src/vm/SPSProfiler.cpp.orig	2016-04-07 21:33:28.000000000 +0000
+++ mozilla/js/src/vm/SPSProfiler.cpp
@@ -4,6 +4,8 @@
  * License, v. 2.0. If a copy of the MPL was not distributed with this
  * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
+#include "jscntxtinlines.h"
+
 #include "vm/SPSProfiler.h"
 
 #include "mozilla/DebugOnly.h"
