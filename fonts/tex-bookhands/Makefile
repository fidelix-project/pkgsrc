# $NetBSD: Makefile,v 1.4 2020/01/18 23:31:15 rillig Exp $

DISTNAME=	bookhands
PKGNAME=	tex-${DISTNAME}-2018
TEXLIVE_REV=	46480

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://ctan.org/pkg/bookhands
COMMENT=	Collection of book-hand fonts
LICENSE=	lppl-1.3c

TEX_MAP_FILES+=	sqrcaps.map

TEXLIVE_UNVERSIONED=	yes
.include "../../print/texlive/package.mk"
.include "../../mk/bsd.pkg.mk"
