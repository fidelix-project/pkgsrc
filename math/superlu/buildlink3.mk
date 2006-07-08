# $NetBSD: buildlink3.mk,v 1.4 2006/07/08 22:39:29 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
SUPERLU_BUILDLINK3_MK:=	${SUPERLU_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	superlu
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nsuperlu}
BUILDLINK_PACKAGES+=	superlu
BUILDLINK_ORDER+=	superlu

.if !empty(SUPERLU_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.superlu+=	superlu>=2.0nb2
BUILDLINK_PKGSRCDIR.superlu?=	../../math/superlu
BUILDLINK_DEPMETHOD.superlu?=	build
.endif	# SUPERLU_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
