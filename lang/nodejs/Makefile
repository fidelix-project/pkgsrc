# $NetBSD: Makefile,v 1.175 2020/03/18 10:03:59 adam Exp $

DISTNAME=	node-v13.11.0

USE_LANGUAGES=	c gnu++14

.include "../../mk/bsd.prefs.mk"

# XXX: figure out a way to add rpaths to torque
MAKE_ENV+=	LD_LIBRARY_PATH=${PREFIX}/lib

CONFIGURE_ARGS+=	--shared-nghttp2
CONFIGURE_ARGS+=	--shared-openssl
CONFIGURE_ARGS+=	--with-intl=system-icu

CHECK_PORTABILITY_SKIP+=	tools/macos-installer/pkgbuild/npm/scripts/preinstall

.if ${MACHINE_ARCH} == "i386"
# 64 bit atomic ops are required
CXXFLAGS+=	-march=i586
# required for SSE2 code under i386.
CXXFLAGS+=	-mstackrealign
.endif

.include "options.mk"

.include "../../lang/nodejs/Makefile.common"
.include "../../textproc/icu/buildlink3.mk"
.include "../../www/nghttp2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
