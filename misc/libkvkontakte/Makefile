# $NetBSD: Makefile,v 1.46 2020/03/10 22:08:55 wiz Exp $

DISTNAME=	libkvkontakte-5.0.0
PKGREVISION=	3
CATEGORIES=	misc
MASTER_SITES=	${MASTER_SITE_KDE:=libkvkontakte/5.0.0/src/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.digikam.org/
COMMENT=	KDE library for asynchronous interaction with vkontakte.ru
LICENSE=	gnu-gpl-v2

.include "../../meta-pkgs/kde/applications.mk"

USE_TOOLS+=	msgmerge pkg-config

.include "../../www/kdewebkit/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
