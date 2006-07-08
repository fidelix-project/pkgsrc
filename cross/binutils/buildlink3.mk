# $NetBSD: buildlink3.mk,v 1.4 2006/07/08 22:39:03 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
CROSS_BINUTILS_BUILDLINK3_MK:=	${CROSS_BINUTILS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	cross-binutils
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ncross-binutils}
BUILDLINK_PACKAGES+=	cross-binutils
BUILDLINK_ORDER+=	cross-binutils

.if !empty(CROSS_BINUTILS_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.cross-binutils+=	cross-binutils>=2.15.0.0nb3
BUILDLINK_PKGSRCDIR.cross-binutils?=	../../cross/binutils
.endif	# CROSS_BINUTILS_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
