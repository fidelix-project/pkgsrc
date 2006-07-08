# $NetBSD: buildlink3.mk,v 1.7 2006/07/08 22:39:42 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
AP2_PERL_BUILDLINK3_MK:=	${AP2_PERL_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	ap2-perl
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nap2-perl}
BUILDLINK_PACKAGES+=	ap2-perl
BUILDLINK_ORDER+=	ap2-perl

.if !empty(AP2_PERL_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.ap2-perl+=	ap2-perl>=2.0.1
BUILDLINK_ABI_DEPENDS.ap2-perl?=	ap2-perl>=2.0.1nb2
BUILDLINK_PKGSRCDIR.ap2-perl?=	../../www/ap2-perl
.endif	# AP2_PERL_BUILDLINK3_MK

.include "../../www/apache2/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
