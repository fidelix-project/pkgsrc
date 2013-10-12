$NetBSD: patch-psutil___psutil__netbsd.h,v 1.1 2013/10/12 13:32:36 wiz Exp $

Port to NetBSD.

--- psutil/_psutil_netbsd.h.orig	2013-10-12 13:19:29.000000000 +0000
+++ psutil/_psutil_netbsd.h
@@ -0,0 +1,50 @@
+/*
+ * Copyright (c) 2009, Giampaolo Rodola'. All rights reserved.
+ * Use of this source code is governed by a BSD-style license that can be
+ * found in the LICENSE file.
+ *
+ * NetBSD platform-specific module methods for _psutil_netbsd
+ */
+
+#include <Python.h>
+
+// --- per-process functions
+
+static PyObject* get_process_cpu_times(PyObject* self, PyObject* args);
+static PyObject* get_process_name(PyObject* self, PyObject* args);
+static PyObject* get_process_exe(PyObject* self, PyObject* args);
+static PyObject* get_process_cmdline(PyObject* self, PyObject* args);
+static PyObject* get_process_ppid(PyObject* self, PyObject* args);
+static PyObject* get_process_uids(PyObject* self, PyObject* args);
+static PyObject* get_process_gids(PyObject* self, PyObject* args);
+static PyObject* get_process_connections(PyObject* self, PyObject* args);
+static PyObject* get_process_create_time(PyObject* self, PyObject* args);
+static PyObject* get_process_memory_info(PyObject* self, PyObject* args);
+static PyObject* get_process_num_threads(PyObject* self, PyObject* args);
+static PyObject* get_process_num_fds(PyObject* self, PyObject* args);
+static PyObject* get_process_threads(PyObject* self, PyObject* args);
+static PyObject* get_process_status(PyObject* self, PyObject* args);
+static PyObject* get_process_io_counters(PyObject* self, PyObject* args);
+static PyObject* get_process_tty_nr(PyObject* self, PyObject* args);
+static PyObject* get_process_memory_maps(PyObject* self, PyObject* args);
+static PyObject* get_process_num_ctx_switches(PyObject* self, PyObject* args);
+#if NOTYET
+static PyObject* get_process_open_files(PyObject* self, PyObject* args);
+static PyObject* get_process_cwd(PyObject* self, PyObject* args);
+#endif
+
+// --- system-related functions
+
+static PyObject* get_pid_list(PyObject* self, PyObject* args);
+static PyObject* get_num_cpus(PyObject* self, PyObject* args);
+static PyObject* get_virtual_mem(PyObject* self, PyObject* args);
+static PyObject* get_swap_mem(PyObject* self, PyObject* args);
+static PyObject* get_system_cpu_times(PyObject* self, PyObject* args);
+#if NOTYET
+static PyObject* get_system_per_cpu_times(PyObject* self, PyObject* args);
+#endif
+static PyObject* get_system_boot_time(PyObject* self, PyObject* args);
+static PyObject* get_disk_partitions(PyObject* self, PyObject* args);
+static PyObject* get_net_io_counters(PyObject* self, PyObject* args);
+static PyObject* get_disk_io_counters(PyObject* self, PyObject* args);
+static PyObject* get_system_users(PyObject* self, PyObject* args);
