# $NetBSD: Makefile,v 1.54 2020/03/04 22:07:29 wiz Exp $

DISTNAME=	pdfgrep-2.1.2
PKGREVISION=	8
CATEGORIES=	textproc
MASTER_SITES=	https://pdfgrep.org/download/

MAINTAINER=	ryoon@NetBSD.org
HOMEPAGE=	https://pdfgrep.org/
COMMENT=	Pdfgrep is a tool to search text in PDF files
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=	yes
USE_LANGUAGES=	c++ c
USE_TOOLS+=	gmake pkg-config

.include "../../devel/pcre/buildlink3.mk"
.include "../../print/poppler-includes/buildlink3.mk"
.include "../../print/poppler-cpp/buildlink3.mk"
.include "../../print/poppler/buildlink3.mk"
.include "../../security/libgcrypt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
