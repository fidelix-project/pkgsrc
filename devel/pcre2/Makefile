# $NetBSD: Makefile,v 1.16 2020/01/26 17:31:02 rillig Exp $

DISTNAME=	pcre2-10.34
CATEGORIES=	devel
MASTER_SITES=	ftp://ftp.pcre.org/pub/pcre/
MASTER_SITES+=	https://ftp.pcre.org/pub/pcre/
MASTER_SITES+=	${MASTER_SITE_SOURCEFORGE:=pcre/}
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.pcre.org/
COMMENT=	Perl Compatible Regular Expressions library (major version 2)
LICENSE=	modified-bsd

USE_LANGUAGES=		c
USE_LIBTOOL=		yes
GNU_CONFIGURE=		yes

PKGCONFIG_OVERRIDE+=	libpcre2-16.pc.in
PKGCONFIG_OVERRIDE+=	libpcre2-posix.pc.in
PKGCONFIG_OVERRIDE+=	libpcre2-8.pc.in
PKGCONFIG_OVERRIDE+=	libpcre2-32.pc.in

CONFIGURE_ARGS+=	--enable-pcre2-16
CONFIGURE_ARGS+=	--enable-pcre2-32
CONFIGURE_ARGS+=	--enable-pcre2grep-libz
CONFIGURE_ARGS+=	--enable-pcre2grep-libbz2
# To avoid having to
# sysctl -w security.pax.mprotect.enabled=0
# because of its JIT on NetBSD.
CONFIGURE_ARGS.NetBSD+=	--enable-jit-sealloc

TEST_TARGET=		check

.include "options.mk"

.include "../../archivers/bzip2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
