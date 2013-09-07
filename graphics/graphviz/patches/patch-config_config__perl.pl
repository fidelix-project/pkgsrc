$NetBSD: patch-config_config__perl.pl,v 1.2 2013/09/07 18:48:43 wiz Exp $

1. chunk: add rpath for pkgsrc
2. chunk: perl-5.18 fix, see
http://www.graphviz.org/mantisbt/view.php?id=2359

--- config/config_perl.pl.orig	2013-08-01 17:35:15.000000000 +0000
+++ config/config_perl.pl
@@ -4,7 +4,7 @@ if ($ARGV[0] eq "PERL_LIBS") {
 	$archlib = $Config{archlib};
 	$libperl = $Config{libperl};
 	$libperl =~ s/lib([^\.]+).*/$1/;
-	print "-L$archlib/CORE -l$libperl";
+	print "-Wl,-rpath,$archlib/CORE -L$archlib/CORE -l$libperl";
 }
 if ($ARGV[0] eq "PERL_INCLUDES") {
 	$archlib = $Config{archlib};
@@ -14,7 +14,7 @@ if ($ARGV[0] eq "PERL_INSTALL_DIR") {
 
 	my $d;
 
-	foreach $d qw(installvendorarch vendorarch installsitearch sitearch) {
+	foreach $d (qw(installvendorarch vendorarch installsitearch sitearch)) {
 		if (exists($Config{$d}) and defined($Config{$d}) and
 			($Config{$d} ne '') ) {
 			print "$Config{$d}";
