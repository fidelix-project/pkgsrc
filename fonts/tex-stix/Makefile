# $NetBSD: Makefile,v 1.5 2020/01/18 23:31:53 rillig Exp $

DISTNAME=	stix
PKGNAME=	tex-${DISTNAME}-1.1.3
TEXLIVE_REV=	47652

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://ctan.org/pkg/stix
COMMENT=	OpenType Unicode maths fonts
LICENSE=	ofl-v1.1 AND lppl-1.3c

TEX_MAP_FILES+=	stix.map

TEXLIVE_UNVERSIONED=	yes
.include "../../print/texlive/package.mk"
.include "../../mk/bsd.pkg.mk"
