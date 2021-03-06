# $NetBSD: Makefile,v 1.26 2020/01/26 17:32:01 rillig Exp $

DISTNAME=	WeasyPrint-50
PKGNAME=	${PYPKGPREFIX}-${DISTNAME:tl}
CATEGORIES=	print python
MASTER_SITES=	${MASTER_SITE_PYPI:=W/WeasyPrint/}

MAINTAINER=	kleink@NetBSD.org
HOMEPAGE=	https://weasyprint.org/
COMMENT=	Converts HTML/CSS documents to PDF
LICENSE=	modified-bsd

BUILD_DEPENDS+=	${PYPKGPREFIX}-test-runner-[0-9]*:../../devel/py-test-runner
DEPENDS+=	pango>=1.29.3:../../devel/pango
DEPENDS+=	${PYPKGPREFIX}-cairosvg>=1.0.20:../../converters/py-cairosvg
DEPENDS+=	${PYPKGPREFIX}-cairocffi>=0.9.0:../../graphics/py-cairocffi
DEPENDS+=	${PYPKGPREFIX}-cffi>=0.6:../../devel/py-cffi
DEPENDS+=	${PYPKGPREFIX}-cssselect2>=0.1:../../textproc/py-cssselect2
DEPENDS+=	${PYPKGPREFIX}-html5lib>=0.999999999:../../textproc/py-html5lib
DEPENDS+=	${PYPKGPREFIX}-pyphen>=0.8:../../textproc/py-pyphen
DEPENDS+=	${PYPKGPREFIX}-tinycss2>=0.5:../../textproc/py-tinycss2
TEST_DEPENDS+=	${PYPKGPREFIX}-test-cov-[0-9]*:../../devel/py-test-cov
TEST_DEPENDS+=	${PYPKGPREFIX}-test-flake8-[0-9]*:../../devel/py-test-flake8
TEST_DEPENDS+=	${PYPKGPREFIX}-test-isort-[0-9]*:../../devel/py-test-isort
TEST_DEPENDS+=	${PYPKGPREFIX}-test-runner-[0-9]*:../../devel/py-test-runner

PYTHON_VERSIONS_INCOMPATIBLE=	27

USE_LANGUAGES=	# none

SUBST_CLASSES+=		pyversfx
SUBST_STAGE.pyversfx=	pre-configure
SUBST_FILES.pyversfx=	setup.cfg
SUBST_VARS.pyversfx=	PYVERSSUFFIX

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
