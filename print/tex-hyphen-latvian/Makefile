# $NetBSD: Makefile,v 1.6 2019/12/06 20:21:40 markd Exp $

DISTNAME=	hyphen-latvian
PKGNAME=	tex-${DISTNAME}-2019.51186
TEXLIVE_REV=	51186

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Latvian hyphenation patterns
LICENSE=	lppl-1.3c

DEPENDS+=	tex-hyphen-base-[0-9]*:../../print/tex-hyphen-base
DEPENDS+=	tex-hyph-utf8-[0-9]*:../../print/tex-hyph-utf8

TEX_HYPHEN_DAT+=	latvian loadhyph-lv.tex
TEX_HYPHEN_DEF+=	\\addlanguage{latvian}{loadhyph-lv.tex}{}{2}{2}
TEX_HYPHEN_LUA+=	['latvian']={ \
			  loader='loadhyph-lv.tex', \
			  lefthyphenmin=2, \
			  righthyphenmin=2, \
			  synonyms={}, \
			  patterns='hyph-lv.pat.txt', \
			  hyphenation='', \
			},

TEXLIVE_UNVERSIONED=	yes
.include "../../print/texlive/package.mk"
.include "../../mk/bsd.pkg.mk"
