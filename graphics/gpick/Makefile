# $NetBSD: Makefile,v 1.26 2020/03/10 22:10:07 wiz Exp $

DISTNAME=	gpick-gpick-0.2.5
PKGNAME=	${DISTNAME:S/gpick-//}
PKGREVISION=	19
CATEGORIES=	graphics
MASTER_SITES=	-http://github.com/thezbyg/gpick/archive/gpick-0.2.5.tar.gz

MAINTAINER=	ryoon@NetBSD.org
HOMEPAGE=	https://github.com/thezbyg/gpick/
COMMENT=	Advanced color picker
LICENSE=	modified-bsd

USE_LANGUAGES=	c c++03
USE_TOOLS+=	pkg-config

PYTHON_VERSIONS_ACCEPTED=	27	# as of 0.2.5

SCONS_ARGS+=	DESTDIR=${DESTDIR}${PREFIX}
SCONS_ARGS+=	PKGMANDIR=${PKGMANDIR}

do-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${SCONSBIN} ${SCONS_ARGS}

do-install:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${SCONSBIN} ${SCONS_ARGS} install

.include "../../devel/boost-libs/buildlink3.mk"
PYTHON_FOR_BUILD_ONLY?=	yes
.include "../../devel/scons/buildlink3.mk"
.include "../../lang/lua/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
