$NetBSD: patch-utils_clflags.mli,v 1.2 2015/06/30 11:08:47 jaapb Exp $

pkgsrc_runtime flag
--- utils/clflags.mli.orig	2015-05-12 15:31:26.000000000 +0000
+++ utils/clflags.mli
@@ -92,6 +92,7 @@ val std_include_dir : unit -> string lis
 val shared : bool ref
 val dlcode : bool ref
 val runtime_variant : string ref
+val pkgsrc_runtime : bool ref
 val force_slash : bool ref
 val keep_docs : bool ref
 val keep_locs : bool ref
