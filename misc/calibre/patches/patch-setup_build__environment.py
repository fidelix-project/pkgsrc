$NetBSD: patch-setup_build__environment.py,v 1.3 2016/09/29 12:13:43 joerg Exp $

Always build like on Linux.

--- setup/build_environment.py.orig	2016-09-29 09:55:14.000000000 +0000
+++ setup/build_environment.py
@@ -97,8 +97,8 @@ def get_sip_dir():
 pyqt['pyqt_sip_dir'] = get_sip_dir()
 pyqt['sip_inc_dir'] = os.environ.get('SIP_INC_DIR', sysconfig.get_path('include'))
 
-glib_flags = subprocess.check_output([PKGCONFIG, '--libs', 'glib-2.0']).strip() if islinux else ''
-fontconfig_flags = subprocess.check_output([PKGCONFIG, '--libs', 'fontconfig']).strip() if islinux else ''
+glib_flags = subprocess.check_output([PKGCONFIG, '--libs', 'glib-2.0']).strip()
+fontconfig_flags = subprocess.check_output([PKGCONFIG, '--libs', 'fontconfig']).strip()
 qt_inc = pyqt['inc']
 qt_lib = pyqt['lib']
 ft_lib_dirs = []
@@ -121,7 +121,7 @@ QT_DLLS = ['Qt5' + x for x in (
 'WebKit', 'WebKitWidgets', 'Widgets',  'Multimedia', 'MultimediaWidgets', 'Xml',  # 'XmlPatterns',
 )]
 QT_PLUGINS = ('imageformats', 'audio', 'iconengines', 'mediaservice', 'platforms', 'playlistformats', 'printsupport', 'sqldrivers')
-if islinux:
+if True:
     # platformthemes cause crashes in Ubuntu
     QT_PLUGINS += ('platforminputcontexts', 'generic',)
 
