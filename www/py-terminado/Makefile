# $NetBSD: Makefile,v 1.4 2019/04/04 07:26:25 adam Exp $

DISTNAME=	terminado-0.8.2
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=	www python
MASTER_SITES=	${MASTER_SITE_PYPI:=t/terminado/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/takluyver/terminado
COMMENT=	Terminals served to term.js using Tornado websockets
LICENSE=	2-clause-bsd

DEPENDS+=	${PYPKGPREFIX}-ptyprocess-[0-9]*:../../sysutils/py-ptyprocess
DEPENDS+=	${PYPKGPREFIX}-tornado>=4:../../www/py-tornado

USE_LANGUAGES=	# none

.include "../../lang/python/distutils.mk"
.include "../../mk/bsd.pkg.mk"
