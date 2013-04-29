# $NetBSD: pyversion.mk,v 1.106 2013/04/29 10:49:37 wiz Exp $

# This file determines which Python version is used as a dependency for
# a package.
#
# === User-settable variables ===
#
# PYTHON_VERSION_DEFAULT
#	The preferred Python version to use.
#
#	Possible values: 26 27 32 33
#	Default: 27
#
# === Infrastructure variables ===
#
# PYTHON_VERSION_REQD
#	Python version to use. This variable should not be set in
#	packages.  Normally it is used by bulk build tools.
#
#	Possible: ${PYTHON_VERSIONS_ACCEPTED}
#	Default:  ${PYTHON_VERSION_DEFAULT}
#
# === Package-settable variables ===
#
# PYTHON_VERSIONS_ACCEPTED
#	The Python versions that are acceptable for the package. The
#	order of the entries matters, since earlier entries are
#	preferred over later ones.
#
#	Possible values: 33 32 27 26
#	Default: (33 32) 27 26
#
# PYTHON_VERSIONS_INCLUDE_3X
#	Wether the default PYTHON_VERSIONS_ACCEPTED should include
#	3.x versions for for this package or not.
#	This variable must be set before including bsd.prefs.mk.
#
#	Possible values: yes no
#	Default: no
#
# PYTHON_VERSIONS_INCOMPATIBLE
#	The Python versions that are NOT acceptable for the package.
#
#	Possible values: 26 27 32 33
#	Default: (depends on the platform)
#
# PYTHON_FOR_BUILD_ONLY
#	Whether Python is needed only at build time or at run time.
#
#	Possible values: (defined) (undefined)
#	Default: (undefined)
#
# PYTHON_SELF_CONFLICT
#	If set to "yes", additional CONFLICTS entries are added for
#	registering a conflict between pyNN-<modulename> packages.
#
#	Possible values: yes no
#	Default: no
#
# === Defined variables ===
#
# PYPKGPREFIX
#	The prefix to use in PKGNAME for extensions which are meant
#	to be installed for multiple Python versions.
#
#	Example: py27
#
# PYVERSSUFFIX
#	The suffix to executables and in the library path, equal to
#	sys.version[0:3].
#
#	Example: 2.7
#
# Keywords: python
#

.if !defined(PYTHON_PYVERSION_MK)
PYTHON_PYVERSION_MK=	defined

# derive a python version from the package name if possible
# optionally handled quoted package names
.if defined(PKGNAME_REQD) && !empty(PKGNAME_REQD:Mpy[0-9][0-9]-*) || \
    defined(PKGNAME_REQD) && !empty(PKGNAME_REQD:M*-py[0-9][0-9]-*)
PYTHON_VERSION_REQD?= ${PKGNAME_REQD:C/(^.*-|^)py([0-9][0-9])-.*/\2/}
.elif defined(PKGNAME_OLD) && !empty(PKGNAME_OLD:Mpy[0-9][0-9]-*) || \
      defined(PKGNAME_OLD) && !empty(PKGNAME_OLD:M*-py[0-9][0-9]-*)
PYTHON_VERSION_REQD?= ${PKGNAME_OLD:C/(^.*-|^)py([0-9][0-9])-.*/\2/}
.endif

.include "../../mk/bsd.prefs.mk"

BUILD_DEFS+=		PYTHON_VERSION_DEFAULT
BUILD_DEFS_EFFECTS+=	PYPACKAGE

PYTHON_VERSION_DEFAULT?=		27
.if ${PYTHON_VERSIONS_INCLUDE_3X:U:tl} == "yes"
PYTHON_VERSIONS_ACCEPTED?=		33 32 27 26
.else
PYTHON_VERSIONS_ACCEPTED?=		27 26
.endif
PYTHON_VERSIONS_INCOMPATIBLE?=		# empty by default

BUILDLINK_API_DEPENDS.python26?=		python26>=2.6
BUILDLINK_API_DEPENDS.python27?=		python27>=2.7
BUILDLINK_API_DEPENDS.python32?=		python32>=3.2
BUILDLINK_API_DEPENDS.python33?=		python33>=3.3

# transform the list into individual variables
.for pv in ${PYTHON_VERSIONS_ACCEPTED}
.if empty(PYTHON_VERSIONS_INCOMPATIBLE:M${pv})
_PYTHON_VERSION_${pv}_OK=	yes
_PYTHON_VERSIONS_ACCEPTED+=	${pv}
.endif
.endfor

#
# choose a python version where to add,
# try to be intelligent
#
# if a version is explicitely required, take it
.if defined(PYTHON_VERSION_REQD)
# but check if it is acceptable first, error out otherwise
. if defined(_PYTHON_VERSION_${PYTHON_VERSION_REQD}_OK)
_PYTHON_VERSION=	${PYTHON_VERSION_REQD}
. endif
.else
# if the default is accepted, it is first choice
. if !defined(_PYTHON_VERSION)
. if defined(_PYTHON_VERSION_${PYTHON_VERSION_DEFAULT}_OK)
_PYTHON_VERSION=	${PYTHON_VERSION_DEFAULT}
. endif
. endif
# prefer an already installed version, in order of "accepted"
. if !defined(_PYTHON_VERSION)
. for pv in ${PYTHON_VERSIONS_ACCEPTED}
. if defined(_PYTHON_VERSION_${pv}_OK)
_PYTHON_VERSION?=	${pv}
. endif
. endfor
. endif
.endif

#
# Variable assignment for multi-python packages
MULTI+=	PYTHON_VERSION_REQD=${_PYTHON_VERSION}

# No supported version found, annotate to simplify statements below.
.if !defined(_PYTHON_VERSION)
_PYTHON_VERSION=	none
.endif

# Additional CONFLICTS
.if ${PYTHON_SELF_CONFLICT:U:tl} == "yes"
.for i in ${PYTHON_VERSIONS_ACCEPTED:N${_PYTHON_VERSION}}
CONFLICTS +=	${PKGNAME:S/py${_PYTHON_VERSION}/py${i}/:C/-[0-9].*$/-[0-9]*/}
.endfor
.endif # PYCONFLICTS

#
PLIST_VARS+=	py2x py3x

.if ${_PYTHON_VERSION} == "33"
PYPKGSRCDIR=	../../lang/python33
PYDEPENDENCY=	${BUILDLINK_API_DEPENDS.python33}:${PYPKGSRCDIR}
PYPACKAGE=	python33
PYVERSSUFFIX=	3.3
PYPKGPREFIX=	py33
PLIST.py3x=	yes
.elif ${_PYTHON_VERSION} == "32"
PYPKGSRCDIR=	../../lang/python32
PYDEPENDENCY=	${BUILDLINK_API_DEPENDS.python32}:${PYPKGSRCDIR}
PYPACKAGE=	python32
PYVERSSUFFIX=	3.2
PYPKGPREFIX=	py32
PLIST.py3x=	yes
.elif ${_PYTHON_VERSION} == "27"
PYPKGSRCDIR=	../../lang/python27
PYDEPENDENCY=	${BUILDLINK_API_DEPENDS.python27}:${PYPKGSRCDIR}
PYPACKAGE=	python27
PYVERSSUFFIX=	2.7
PYPKGPREFIX=	py27
PLIST.py2x=	yes
.elif ${_PYTHON_VERSION} == "26"
PYPKGSRCDIR=	../../lang/python26
PYDEPENDENCY=	${BUILDLINK_API_DEPENDS.python26}:${PYPKGSRCDIR}
PYPACKAGE=	python26
PYVERSSUFFIX=	2.6
PYPKGPREFIX=	py26
PLIST.py2x=	yes
.else
PKG_FAIL_REASON+=   "No valid Python version"
PYPKGPREFIX=
.endif

PTHREAD_OPTS+=	require
.include "../../mk/pthread.buildlink3.mk"

.if defined(PYTHON_FOR_BUILD_ONLY)
BUILDLINK_DEPMETHOD.python?=	build
.endif
.if defined(PYPKGSRCDIR)
.include "${PYPKGSRCDIR}/buildlink3.mk"
.endif

PYTHONBIN=	${LOCALBASE}/bin/python${PYVERSSUFFIX}
PYTHONCONFIG=	${LOCALBASE}/bin/python${PYVERSSUFFIX}-config
PY_COMPILE_ALL= \
	${PYTHONBIN} ${PREFIX}/lib/python${PYVERSSUFFIX}/compileall.py -q
PY_COMPILE_O_ALL= \
	${PYTHONBIN} -O ${PREFIX}/lib/python${PYVERSSUFFIX}/compileall.py -q

.if exists(${PYTHONBIN})
PYINC!=	${PYTHONBIN} -c "import distutils.sysconfig; \
	print (distutils.sysconfig.get_python_inc(0, \"\"))" || ${ECHO} ""
PYLIB!=	${PYTHONBIN} -c "import distutils.sysconfig; \
	print (distutils.sysconfig.get_python_lib(0, 1, \"\"))" || ${ECHO} ""
PYSITELIB!=	${PYTHONBIN} -c "import distutils.sysconfig; \
	print (distutils.sysconfig.get_python_lib(0, 0, \"\"))" || ${ECHO} ""

PRINT_PLIST_AWK+=	/^${PYINC:S|/|\\/|g}/ \
			{ gsub(/${PYINC:S|/|\\/|g}/, "$${PYINC}") }
PRINT_PLIST_AWK+=	/^${PYSITELIB:S|/|\\/|g}/ \
			{ gsub(/${PYSITELIB:S|/|\\/|g}/, "$${PYSITELIB}") }
PRINT_PLIST_AWK+=	/^${PYLIB:S|/|\\/|g}/ \
			{ gsub(/${PYLIB:S|/|\\/|g}/, "$${PYLIB}") }
.endif

ALL_ENV+=	PYTHON=${PYTHONBIN}
.if defined(USE_CMAKE)
# used by FindPythonInterp.cmake and FindPythonLibs.cmake
CMAKE_ARGS+=	-DPYVERSSUFFIX:STRING=${PYVERSSUFFIX}
.endif

.endif	# PYTHON_PYVERSION_MK
