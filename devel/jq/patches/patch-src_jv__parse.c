$NetBSD: patch-src_jv__parse.c,v 1.1 2016/05/10 09:20:52 tnn Exp $

CVE-2015-8863

From 8eb1367ca44e772963e704a700ef72ae2e12babd Mon Sep 17 00:00:00 2001
From: Nicolas Williams <nico@cryptonector.com>
Date: Sat, 24 Oct 2015 17:24:57 -0500
Subject: [PATCH] Heap buffer overflow in tokenadd() (fix #105)

This was an off-by one: the NUL terminator byte was not allocated on
resize.  This was triggered by JSON-encoded numbers longer than 256
bytes.
---
 src/jv_parse.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

diff --git a/src/jv_parse.c b/src/jv_parse.c
index 3102ed4..84245b8 100644
--- jv_parse.c
+++ jv_parse.c
@@ -383,7 +383,7 @@ static pfunc stream_token(struct jv_parser* p, char ch) {
 
 static void tokenadd(struct jv_parser* p, char c) {
   assert(p->tokenpos <= p->tokenlen);
-  if (p->tokenpos == p->tokenlen) {
+  if (p->tokenpos >= (p->tokenlen - 1)) {
     p->tokenlen = p->tokenlen*2 + 256;
     p->tokenbuf = jv_mem_realloc(p->tokenbuf, p->tokenlen);
   }
@@ -485,7 +485,7 @@ static pfunc check_literal(struct jv_parser* p) {
     TRY(value(p, v));
   } else {
     // FIXME: better parser
-    p->tokenbuf[p->tokenpos] = 0; // FIXME: invalid
+    p->tokenbuf[p->tokenpos] = 0;
     char* end = 0;
     double d = jvp_strtod(&p->dtoa, p->tokenbuf, &end);
     if (end == 0 || *end != 0)
