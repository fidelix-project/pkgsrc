# $NetBSD: buildlink3.mk,v 1.10 2006/06/04 20:29:40 joerg Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
AP_PERL_BUILDLINK3_MK:=	${AP_PERL_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	ap13-perl
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nap-perl}
BUILDLINK_PACKAGES+=	ap13-perl

.if !empty(AP_PERL_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.ap13-perl+=	ap13-perl>=1.29nb3
BUILDLINK_ABI_DEPENDS.ap13-perl?=	ap13-perl>=1.29nb5
BUILDLINK_PKGSRCDIR.ap13-perl?=	../../www/ap-perl

BUILDLINK_FILES.ap13-perl+=	lib/httpd/mod_perl.*
BUILDLINK_FILES.ap13-perl+=	\
	${PERL5_SUB_INSTALLVENDORARCH}/auto/Apache/include/*
BUILDLINK_FILES.ap13-perl+=	\
	${PERL5_SUB_INSTALLVENDORARCH}/auto/Apache/include/modules/perl/*
.endif	# AP_PERL_BUILDLINK3_MK

.include "../../www/apache/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
