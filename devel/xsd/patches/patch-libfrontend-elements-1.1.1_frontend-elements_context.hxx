$NetBSD: patch-libfrontend-elements-1.1.1_frontend-elements_context.hxx,v 1.1 2013/05/21 16:36:22 joerg Exp $

--- libfrontend-elements-1.1.1/frontend-elements/context.hxx.orig	2013-05-14 19:57:57.000000000 +0000
+++ libfrontend-elements-1.1.1/frontend-elements/context.hxx
@@ -111,7 +111,7 @@ namespace FrontendElements
     Void
     remove (Char const* key)
     {
-      Map::Iterator i (map_.find (key));
+      Map::ConstIterator i (map_.find (key));
 
       if (i == map_.end ())
         throw NoEntry ();
