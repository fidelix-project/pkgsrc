package main

import "gopkg.in/check.v1"

func (s *Suite) Test_ChecklinesPlist(c *check.C) {
	t := s.Init(c)

	t.SetupCommandLine("-Wall")
	G.Pkg = NewPackage("category/pkgbase")
	lines := t.NewLines("PLIST",
		"bin/i386/6c",
		"bin/program",
		"etc/my.cnf",
		"etc/rc.d/service",
		"@exec ${MKDIR} include/pkgbase",
		"info/dir",
		"lib/c.so",
		"lib/libc.so.6",
		"lib/libc.la",
		"${PLIST.man}man/cat3/strcpy.4",
		"man/man1/imake.${IMAKE_MANNEWSUFFIX}",
		"${PLIST.obsolete}@unexec rmdir /tmp",
		"sbin/clockctl",
		"share/icons/gnome/delete-icon",
		"share/icons/hicolor/icon1.png",
		"share/icons/hicolor/icon2.png", // No additional warning
		"share/tzinfo",
		"share/tzinfo")

	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"ERROR: PLIST:1: Expected \"@comment $"+"NetBSD$\".",
		"WARN: PLIST:1: The bin/ directory should not have subdirectories.",
		"ERROR: PLIST:3: Configuration files must not be registered in the PLIST. "+
			"Please use the CONF_FILES framework, which is described in mk/pkginstall/bsd.pkginstall.mk.",
		"ERROR: PLIST:4: RCD_SCRIPTS must not be registered in the PLIST. Please use the RCD_SCRIPTS framework.",
		"ERROR: PLIST:6: \"info/dir\" must not be listed. Use install-info to add/remove an entry.",
		"WARN: PLIST:7: Library filename \"c.so\" should start with \"lib\".",
		"WARN: PLIST:8: Redundant library found. The libtool library is in line 9.",
		"WARN: PLIST:9: \"lib/libc.la\" should be sorted before \"lib/libc.so.6\".",
		"WARN: PLIST:10: Preformatted manual page without unformatted one.",
		"WARN: PLIST:10: Preformatted manual pages should end in \".0\".",
		"WARN: PLIST:11: IMAKE_MANNEWSUFFIX is not meant to appear in PLISTs.",
		"WARN: PLIST:12: Please remove this line. It is no longer necessary.",
		"ERROR: PLIST:14: The package Makefile must include \"../../graphics/gnome-icon-theme/buildlink3.mk\".",
		"WARN: PLIST:14: Packages that install icon theme files should set ICON_THEMES.",
		"ERROR: PLIST:15: Packages that install hicolor icons "+
			"must include \"../../graphics/hicolor-icon-theme/buildlink3.mk\" in the Makefile.",
		"ERROR: PLIST:18: Duplicate filename \"share/tzinfo\", already appeared in line 17.")
}

func (s *Suite) Test_ChecklinesPlist__empty(c *check.C) {
	t := s.Init(c)

	lines := t.NewLines("PLIST",
		PlistRcsId)

	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"WARN: PLIST:1: PLIST files shouldn't be empty.")
}

func (s *Suite) Test_ChecklinesPlist__commonEnd(c *check.C) {
	t := s.Init(c)

	t.SetupFileLines("PLIST.common",
		PlistRcsId,
		"bin/common")
	lines := t.SetupFileLines("PLIST.common_end",
		PlistRcsId,
		"sbin/common_end")

	ChecklinesPlist(lines)

	t.CheckOutputEmpty()
}

func (s *Suite) Test_ChecklinesPlist__conditional(c *check.C) {
	t := s.Init(c)

	G.Pkg = NewPackage("category/pkgbase")
	G.Pkg.plistSubstCond["PLIST.bincmds"] = true
	lines := t.NewLines("PLIST",
		PlistRcsId,
		"${PLIST.bincmds}bin/subdir/command")

	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"WARN: PLIST:2: The bin/ directory should not have subdirectories.")
}

func (s *Suite) Test_ChecklinesPlist__sorting(c *check.C) {
	t := s.Init(c)

	t.SetupCommandLine("-Wplist-sort")
	lines := t.NewLines("PLIST",
		PlistRcsId,
		"@comment Do not remove",
		"sbin/i386/6c",
		"sbin/program",
		"bin/otherprogram",
		"${PLIST.conditional}bin/cat")

	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"WARN: PLIST:5: \"bin/otherprogram\" should be sorted before \"sbin/program\".",
		"WARN: PLIST:6: \"bin/cat\" should be sorted before \"bin/otherprogram\".")
}

func (s *Suite) Test_PlistLineSorter_Sort(c *check.C) {
	t := s.Init(c)

	t.SetupCommandLine("--autofix")
	lines := t.SetupFileLines("PLIST",
		PlistRcsId,
		"@comment Do not remove",
		"A",
		"b",
		"CCC",
		"lib/${UNKNOWN}.la",
		"C",
		"ddd",
		"@exec echo \"after ddd\"", // Makes the PLIST unsortable
		"sbin/program",
		"${PLIST.one}bin/program",
		"man/man1/program.1",
		"${PLIST.two}bin/program2",
		"lib/before.la",
		"${PLIST.linux}${PLIST.x86_64}lib/lib-linux-x86_64.so", // Double conditional, see graphics/graphviz
		"lib/after.la",
		"@exec echo \"after lib/after.la\"")
	ck := &PlistChecker{nil, nil, "", Once{}}
	plines := ck.NewLines(lines)

	sorter1 := NewPlistLineSorter(plines)
	c.Check(sorter1.unsortable, equals, lines[5])

	cleanedLines := append(append(lines[0:5], lines[6:8]...), lines[9:]...) // Remove ${UNKNOWN} and @exec

	sorter2 := NewPlistLineSorter((&PlistChecker{nil, nil, "", Once{}}).NewLines(cleanedLines))

	c.Check(sorter2.unsortable, check.IsNil)

	sorter2.Sort()

	t.CheckOutputLines(
		"AUTOFIX: ~/PLIST:3: Sorting the whole file.")
	t.CheckFileLines("PLIST",
		PlistRcsId,
		"@comment Do not remove", // The header ends here
		"A",
		"C",
		"CCC",
		"b",
		"${PLIST.one}bin/program", // Conditionals are ignored while sorting
		"${PLIST.two}bin/program2",
		"ddd",
		"lib/after.la",
		"lib/before.la",
		"${PLIST.linux}${PLIST.x86_64}lib/lib-linux-x86_64.so",
		"man/man1/program.1",
		"sbin/program",
		"@exec echo \"after lib/after.la\"") // The footer starts here
}

func (s *Suite) Test_PlistChecker_checkpathShare_Desktop(c *check.C) {
	// Disabled due to PR 46570, item "10. It should stop".
	return

	t := s.Init(c)

	t.SetupCommandLine("-Wextra")
	G.Pkg = NewPackage("category/pkgpath")

	ChecklinesPlist(t.NewLines("PLIST",
		PlistRcsId,
		"share/applications/pkgbase.desktop"))

	t.CheckOutputLines(
		"WARN: PLIST:2: Packages that install a .desktop entry " +
			"should .include \"../../sysutils/desktop-file-utils/desktopdb.mk\".")
}

func (s *Suite) Test_PlistChecker_checkpathMan_gz(c *check.C) {
	t := s.Init(c)

	G.Pkg = NewPackage("category/pkgbase")
	lines := t.NewLines("PLIST",
		PlistRcsId,
		"man/man3/strerror.3.gz")

	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"NOTE: PLIST:2: The .gz extension is unnecessary for manual pages.")
}

func (s *Suite) TestPlistChecker_checkpath__PKGMANDIR(c *check.C) {
	t := s.Init(c)

	lines := t.NewLines("PLIST",
		PlistRcsId,
		"${PKGMANDIR}/man1/sh.1")

	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"NOTE: PLIST:2: PLIST files should mention \"man/\" instead of \"${PKGMANDIR}\".")
}

func (s *Suite) TestPlistChecker_checkpath__python_egg(c *check.C) {
	t := s.Init(c)

	lines := t.NewLines("PLIST",
		PlistRcsId,
		"${PYSITELIB}/gdspy-${PKGVERSION}-py${PYVERSSUFFIX}.egg-info/PKG-INFO")

	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"WARN: PLIST:2: Include \"../../lang/python/egg.mk\" instead of listing .egg-info files directly.")
}

func (s *Suite) Test_PlistChecker__autofix(c *check.C) {
	t := s.Init(c)

	t.SetupCommandLine("-Wall")

	fname := t.CreateFileLines("PLIST",
		PlistRcsId,
		"lib/libvirt/connection-driver/libvirt_driver_storage.la",
		"${PLIST.hal}lib/libvirt/connection-driver/libvirt_driver_nodedev.la",
		"${PLIST.xen}lib/libvirt/connection-driver/libvirt_driver_libxl.la",
		"lib/libvirt/lock-driver/lockd.la",
		"${PKGMANDIR}/man1/sh.1",
		"share/augeas/lenses/virtlockd.aug",
		"share/doc/pkgname-1.0/html/32favicon.png",
		"share/doc/pkgname-1.0/html/404.html",
		"share/doc/pkgname-1.0/html/acl.html",
		"share/doc/pkgname-1.0/html/aclpolkit.html",
		"share/doc/pkgname-1.0/html/windows.html",
		"share/examples/libvirt/libvirt.conf",
		"share/locale/zh_CN/LC_MESSAGES/libvirt.mo",
		"share/locale/zh_TW/LC_MESSAGES/libvirt.mo",
		"share/locale/zu/LC_MESSAGES/libvirt.mo",
		"@pkgdir share/examples/libvirt/nwfilter",
		"@pkgdir        etc/libvirt/qemu/networks/autostart",
		"@pkgdir        etc/logrotate.d",
		"@pkgdir        etc/sasl2")
	lines := LoadExistingLines(fname, false)
	ChecklinesPlist(lines)

	t.CheckOutputLines(
		"WARN: ~/PLIST:3: \"lib/libvirt/connection-driver/libvirt_driver_nodedev.la\" "+
			"should be sorted before \"lib/libvirt/connection-driver/libvirt_driver_storage.la\".",
		"WARN: ~/PLIST:4: \"lib/libvirt/connection-driver/libvirt_driver_libxl.la\" "+
			"should be sorted before \"lib/libvirt/connection-driver/libvirt_driver_nodedev.la\".",
		"NOTE: ~/PLIST:6: PLIST files should mention \"man/\" instead of \"${PKGMANDIR}\".")

	t.SetupCommandLine("-Wall", "--autofix")
	ChecklinesPlist(lines)

	fixedLines := LoadExistingLines(fname, false)

	t.CheckOutputLines(
		"AUTOFIX: ~/PLIST:6: Replacing \"${PKGMANDIR}/\" with \"man/\".",
		"AUTOFIX: ~/PLIST:2: Sorting the whole file.")
	c.Check(len(lines), equals, len(fixedLines))
	t.CheckFileLines("PLIST",
		PlistRcsId,
		"${PLIST.xen}lib/libvirt/connection-driver/libvirt_driver_libxl.la",
		"${PLIST.hal}lib/libvirt/connection-driver/libvirt_driver_nodedev.la",
		"lib/libvirt/connection-driver/libvirt_driver_storage.la",
		"lib/libvirt/lock-driver/lockd.la",
		"man/man1/sh.1",
		"share/augeas/lenses/virtlockd.aug",
		"share/doc/pkgname-1.0/html/32favicon.png",
		"share/doc/pkgname-1.0/html/404.html",
		"share/doc/pkgname-1.0/html/acl.html",
		"share/doc/pkgname-1.0/html/aclpolkit.html",
		"share/doc/pkgname-1.0/html/windows.html",
		"share/examples/libvirt/libvirt.conf",
		"share/locale/zh_CN/LC_MESSAGES/libvirt.mo",
		"share/locale/zh_TW/LC_MESSAGES/libvirt.mo",
		"share/locale/zu/LC_MESSAGES/libvirt.mo",
		"@pkgdir share/examples/libvirt/nwfilter",
		"@pkgdir        etc/libvirt/qemu/networks/autostart",
		"@pkgdir        etc/logrotate.d",
		"@pkgdir        etc/sasl2")
}
