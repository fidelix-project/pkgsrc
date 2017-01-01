$NetBSD: patch-mozilla_toolkit_components_protobuf_src_google_protobuf_stubs_atomicops.h,v 1.2 2017/01/01 16:14:08 ryoon Exp $

--- mozilla/toolkit/components/protobuf/src/google/protobuf/stubs/atomicops.h.orig	2016-12-14 02:06:57.000000000 +0000
+++ mozilla/toolkit/components/protobuf/src/google/protobuf/stubs/atomicops.h
@@ -76,6 +76,11 @@ typedef intptr_t Atomic64;
 #endif
 #endif
 
+#if defined(__NetBSD__) && defined(__arm__)
+// NetBSD/arm uses long for intptr_t, which fails -fpermissive checks. So
+// explicitly use int32 here instead.
+typedef int32 AtomicWord;
+#else
 // Use AtomicWord for a machine-sized pointer.  It will use the Atomic32 or
 // Atomic64 routines below, depending on your architecture.
 #if defined(__OpenBSD__) && !defined(GOOGLE_PROTOBUF_ARCH_64_BIT)
@@ -83,6 +88,7 @@ typedef Atomic32 AtomicWord;
 #else
 typedef intptr_t AtomicWord;
 #endif
+#endif
 
 // Atomically execute:
 //      result = *ptr;
