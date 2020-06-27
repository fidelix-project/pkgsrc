# $NetBSD: Makefile,v 1.48 2020/03/08 16:47:59 wiz Exp $

DISTNAME=	gstreamer-1.16.2
PKGNAME=	${DISTNAME:S/gstreamer/gstreamer1/}
PKGREVISION=	1
CATEGORIES=	multimedia
MASTER_SITES=	https://gstreamer.freedesktop.org/src/gstreamer/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://gstreamer.freedesktop.org/
COMMENT=	Open source multimedia framework
LICENSE=	gnu-lgpl-v2

USE_LIBTOOL=		yes
USE_PKGLOCALEDIR=	yes
USE_TOOLS+=		bison flex gmake perl pkg-config
.if "${OS_VARIANT}" != "Fidelix"
GNU_CONFIGURE=		yes
.endif
TEST_TARGET=		check
FLEX_REQD=		2.5.31

.include "options.mk"

PKGCONFIG_OVERRIDE+=	pkgconfig/gstreamer-controller.pc.in
PKGCONFIG_OVERRIDE+=	pkgconfig/gstreamer-check.pc.in
PKGCONFIG_OVERRIDE+=	pkgconfig/gstreamer-net.pc.in
PKGCONFIG_OVERRIDE+=	pkgconfig/gstreamer.pc.in
PKGCONFIG_OVERRIDE+=	pkgconfig/gstreamer-base.pc.in

.if ${OS_VARIANT} == "Fidelix"
BUILD_DEPENDS+=         libexecinfo>=1.1:../../devel/libexecinfo
DEPENDS+=               libexecinfo>=1.1:../../devel/libexecinfo
USE_TOOLS+=		python3
TOOLS_PLATFORM.python3=	${PYTHONBIN}
.include "../../devel/libexecinfo/buildlink3.mk"
.include "../../devel/meson/build.mk"
.include "../../lang/python/pyversion.mk"
.endif

.include "../../devel/glib2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
