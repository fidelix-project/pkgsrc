# $NetBSD: Makefile,v 1.12 2020/01/02 03:27:12 pho Exp $

DISTNAME=		cpphs-1.20.8
CATEGORIES=		devel

MAINTAINER=		esg@sdf.lonestar.org
COMMENT=		Liberalised re-implementation of cpp, the C pre-processor
LICENSE=		gnu-lgpl-v2.1

INSTALLATION_DIRS+=	${PKGMANDIR}/man1

post-install:
	${INSTALL_MAN} ${WRKSRC}/docs/cpphs.1 ${DESTDIR}${PREFIX}/${PKGMANDIR}/man1

.include "../../mk/haskell.mk"
.include "../../devel/hs-old-locale/buildlink3.mk"
.include "../../time/hs-old-time/buildlink3.mk"
.include "../../textproc/hs-polyparse/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
