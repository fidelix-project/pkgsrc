# $NetBSD: Makefile,v 1.97 2020/03/10 22:09:28 wiz Exp $

PKGNAME=	libpurple-${PIDGIN_VERSION}
PKGREVISION=	11

COMMENT=	Multi-protocol Instant Messaging client backend

.include		"../../chat/libpurple/Makefile.common"

USE_TOOLS+=		msgfmt intltool

CPPFLAGS.SunOS+=	-D__SunOS

.include "options.mk"

BUILD_DIRS=	m4macros libpurple po share/ca-certs share/sounds

.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/libidn/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
