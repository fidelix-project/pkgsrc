# $NetBSD: Makefile,v 1.5 2019/12/06 20:23:28 markd Exp $

DISTNAME=	texlive-docindex.doc
PKGNAME=	tex-${DISTNAME:S/./-/}-2014
TEXLIVE_REV=	36749

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Documentation for tex-texlive-docindex

SUBST_CLASSES+=		paths
SUBST_MESSAGE.paths=	Setting paths to documentation files.
SUBST_STAGE.paths=	pre-configure
SUBST_FILES.paths=	doc.html
SUBST_SED.paths=	-e 's,<a href="texmf,<a href="../../texmf,g'

INSTALLATION_DIRS+=	share/doc/texlive

TEXLIVE_UNVERSIONED=	yes
.include "../../print/texlive/package.mk"

do-install:
	${INSTALL_DATA} ${WRKSRC}/doc.html \
		${DESTDIR}${PREFIX}/share/doc/texlive/

.include "../../mk/bsd.pkg.mk"
