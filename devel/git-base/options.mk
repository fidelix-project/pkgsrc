# $NetBSD: options.mk,v 1.2 2014/01/03 17:31:25 richard Exp $
#
PKG_OPTIONS_VAR=	PKG_OPTIONS.git
PKG_SUPPORTED_OPTIONS=	python
# python is not suggested because upstream's INSTALL does not list python
# as a dependency and because all it does is install a python module,
# which does not seem worth the dependency for everyone else.
PKG_SUGGESTED_OPTIONS=

.include "../../mk/bsd.options.mk"

PLIST_VARS+=		python

.if !empty(PKG_OPTIONS:Mpython)
PY_PATCHPLIST=	yes
CONFIGURE_ARGS+=	--with-python=${PYTHONBIN}
PLIST.python=		yes
# not executable
CHECK_INTERPRETER_SKIP+= ${PYSITELIB}/git_remote_helpers/*.py
CHECK_INTERPRETER_SKIP+= ${PYSITELIB}/git_remote_helpers/git/*.py
.include "../../lang/python/application.mk"
.include "../../lang/python/extension.mk"
.else
CONFIGURE_ARGS+=	--without-python
.endif
