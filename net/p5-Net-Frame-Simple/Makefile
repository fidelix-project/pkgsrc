# $NetBSD: Makefile,v 1.16 2019/08/11 13:22:19 wiz Exp $

DISTNAME=	Net-Frame-Simple-1.09
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	2
CATEGORIES=	net perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Net/}

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Frame crafting made easy
HOMEPAGE=	https://metacpan.org/release/Net-Frame-Simple
LICENSE=	artistic

DEPENDS+=	p5-Class-Gomor>=1.0:../../devel/p5-Class-Gomor
DEPENDS+=	p5-Net-Frame-[0-9]*:../../net/p5-Net-Frame

PERL5_PACKLIST=		auto/Net/Frame/Simple/.packlist

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
