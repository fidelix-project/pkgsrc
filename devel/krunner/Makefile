# $NetBSD: Makefile,v 1.33 2020/03/10 22:08:42 wiz Exp $

DISTNAME=	krunner-${KF5VER}
PKGREVISION=	2
CATEGORIES=	devel

HOMEPAGE=	https://community.kde.org/Frameworks
COMMENT=	Framework for providing different actions given a string query
LICENSE=	gnu-lgpl-v2.1

.include "../../meta-pkgs/kde/kf5.mk"

USE_TOOLS+=	msgmerge

.include "../../x11/plasma-framework/buildlink3.mk"
.include "../../devel/threadweaver/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
