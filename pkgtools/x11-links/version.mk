# $NetBSD: version.mk,v 1.1 2005/06/01 18:03:08 jlam Exp $
#
# This Makefile fragment is included by Makefiles that need to access
# the X11_TYPE and version number of a native X11 distribution.
#
# The following variables are provided by this file:
#
#    BUILTIN_X11_TYPE.native is the X11_TYPE of the native X11
#	distribution detected on the system.
#
#    BUILTIN_X11_VERSION.native is the version number, where applicable,
#	of the native X11 distribution detected on the system.
#

.if !defined(BUILTIN_X11_VERSION.native)
.  include "../../x11/xorg-libs/version.mk"
.  include "../../x11/XFree86-libs/version.mk"

.  if defined(BUILTIN_X11_VERSION.xorg)
BUILTIN_X11_TYPE.native=	${BUILTIN_X11_TYPE.xorg}
BUILTIN_X11_VERSION.native=	${BUILTIN_X11_VERSION.xorg}
.  elif defined(BUILTIN_X11_VERSION.XFree86)
BUILTIN_X11_TYPE.native=	${BUILTIN_X11_TYPE.XFree86}
BUILTIN_X11_VERSION.native=	${BUILTIN_X11_VERSION.XFree86}
.  elif !empty(X11BASE:M*openwin)
BUILTIN_X11_TYPE.native=	openwin
.  elif ${OPSYS} == "IRIX"
BUILTIN_X11_TYPE.native=	xsgi
.  elif ${OPSYS} == "OSF1"
BUILTIN_X11_TYPE.native=	xdec
.  else
BUILTIN_X11_TYPE.native=	unknown
.  endif
.endif
MAKEVARS+=	BUILTIN_X11_VERSION.native
