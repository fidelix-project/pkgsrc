# $NetBSD: Makefile,v 1.3 2020/03/10 22:09:58 wiz Exp $

DISTNAME=	oshu-2.0.0
PKGREVISION=	2
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=fmang/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/fmang/oshu
COMMENT=	Fast osu! port
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++14
USE_CMAKE=	yes

CMAKE_ARGS+=	-DOSHU_SKINS="minimal;osu"

.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/pango/buildlink3.mk"
.include "../../graphics/cairo/buildlink3.mk"
.include "../../graphics/SDL2_image/buildlink3.mk"
.include "../../multimedia/ffmpeg4/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
