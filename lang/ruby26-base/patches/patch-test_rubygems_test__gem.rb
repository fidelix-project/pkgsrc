$NetBSD: patch-test_rubygems_test__gem.rb,v 1.1 2019/02/03 13:41:33 taca Exp $

* Use vendordir instead of sitedir.

--- test/rubygems/test_gem.rb.orig	2017-03-17 04:36:49.000000000 +0000
+++ test/rubygems/test_gem.rb
@@ -712,12 +712,12 @@ class TestGem < Gem::TestCase
   end
 
   def test_self_prefix_sitelibdir
-    orig_sitelibdir = RbConfig::CONFIG['sitelibdir']
+    orig_sitelibdir = RbConfig::CONFIG['vendorlibdir']
     RbConfig::CONFIG['sitelibdir'] = @@project_dir
 
     assert_nil Gem.prefix
   ensure
-    RbConfig::CONFIG['sitelibdir'] = orig_sitelibdir
+    RbConfig::CONFIG['vendorlibdir'] = orig_sitelibdir
   end
 
   def test_self_read_binary
