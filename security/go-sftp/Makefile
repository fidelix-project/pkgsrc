# $NetBSD: Makefile,v 1.20 2020/03/21 16:57:04 bsiegert Exp $

DISTNAME=	sftp-1.0.0
PKGNAME=	go-${DISTNAME}
PKGREVISION=	17
MASTER_SITES=	${MASTER_SITE_GITHUB:=pkg/}
CATEGORIES=	security
GITHUB_TAG=	${PKGVERSION_NOREV}
GITHUB_PROJECT=	${PKGBASE:S/^go-//}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/pkg/sftp
COMMENT=	SFTP support for the go.crypto/ssh package
LICENSE=	2-clause-bsd

GO_DIST_BASE=	${DISTNAME}
GO_SRCPATH=	github.com/pkg/sftp

.include "../../devel/go-fs/buildlink3.mk"
.include "../../devel/go-errors/buildlink3.mk"
.include "../../security/go-crypto/buildlink3.mk"
.include "../../lang/go/go-package.mk"
.include "../../mk/bsd.pkg.mk"
