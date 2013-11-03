$NetBSD: patch-src_vax_ffitarget.h,v 1.1 2013/11/03 23:51:51 jklos Exp $

--- src/vax/ffitarget.h.orig	2013-11-03 23:03:01.000000000 +0000
+++ src/vax/ffitarget.h
@@ -0,0 +1,49 @@
+/*
+ * Copyright (c) 2013 Miodrag Vallat.  <miod@openbsd.org>
+ *
+ * Permission is hereby granted, free of charge, to any person obtaining
+ * a copy of this software and associated documentation files (the
+ * ``Software''), to deal in the Software without restriction, including
+ * without limitation the rights to use, copy, modify, merge, publish,
+ * distribute, sublicense, and/or sell copies of the Software, and to
+ * permit persons to whom the Software is furnished to do so, subject to
+ * the following conditions:
+ * 
+ * The above copyright notice and this permission notice shall be included
+ * in all copies or substantial portions of the Software.
+ * 
+ * THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND,
+ * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
+ * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
+ * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
+ * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
+ * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
+ * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
+ */
+
+/*
+ * vax Foreign Function Interface
+ */
+
+#ifndef LIBFFI_TARGET_H
+#define LIBFFI_TARGET_H
+
+#ifndef LIBFFI_ASM
+typedef unsigned long ffi_arg;
+typedef signed long ffi_sarg;
+
+typedef enum ffi_abi {
+  FFI_FIRST_ABI = 0,
+  FFI_ELFBSD,
+  FFI_DEFAULT_ABI = FFI_ELFBSD,
+  FFI_LAST_ABI = FFI_DEFAULT_ABI + 1
+} ffi_abi;
+#endif
+
+/* ---- Definitions for closures ----------------------------------------- */
+
+#define FFI_CLOSURES 1
+#define FFI_TRAMPOLINE_SIZE 15
+#define FFI_NATIVE_RAW_API 0
+
+#endif
