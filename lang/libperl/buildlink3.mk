# $NetBSD: buildlink3.mk,v 1.6 2004/03/05 19:25:36 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBPERL_BUILDLINK3_MK:=	${LIBPERL_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libperl
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibperl}
BUILDLINK_PACKAGES+=	libperl

.if !empty(LIBPERL_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libperl+=	{libperl>=${LIBPERL5_REQD},perl>=5.8.0}
BUILDLINK_PKGSRCDIR.libperl?=	../../lang/libperl

LIBPERL5_REQD?=		${_PERL5_REQD}

.include "../../lang/perl5/buildlink3.mk"

.endif	# LIBPERL_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
