# $NetBSD: Makefile,v 1.1 2019/09/18 15:32:47 ryoon Exp $

.include "../../cross/mingw-w64-x86_64-winpthreads/Makefile.common"

PKGNAME=		${DISTNAME:S/mingw-w64-v/mingw-w64-i686-winpthreads-/}
COMMENT=		Mingw-w64 winpthreads library  for win32 cross-development

BUILD_DEPENDS+=		mingw-w64-i686-gcc-bootstrap-[0-9]*:../../cross/mingw-w64-i686-gcc-bootstrap

MINGW_TARGET=		${MINGW_W64_32_TARGET}
CONFIGURE_ARGS+=	--enable-lib32
CONFIGURE_ARGS+=	--disable-lib64

BUILDLINK_DEPMETHOD.mingw-w64-i686-headers=	build
.include "../../cross/mingw-w64-i686-headers/buildlink3.mk"
BUILDLINK_DEPMETHOD.mingw-w64-i686-crt=		build
.include "../../cross/mingw-w64-i686-crt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
