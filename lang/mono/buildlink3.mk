# $NetBSD: buildlink3.mk,v 1.22 2006/07/08 22:39:23 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
MONO_BUILDLINK3_MK:=	${MONO_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	mono
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nmono}
BUILDLINK_PACKAGES+=	mono
BUILDLINK_ORDER+=	mono

.if !empty(MONO_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.mono+=	mono>=1.1.12.1
BUILDLINK_ABI_DEPENDS.mono?=	mono>=1.1.12.1nb2
BUILDLINK_PKGSRCDIR.mono?=	../../lang/mono
.endif	# MONO_BUILDLINK3_MK

.include "../../devel/glib2/buildlink3.mk"
.include "../../textproc/icu/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
