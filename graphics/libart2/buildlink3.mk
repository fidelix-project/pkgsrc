# $NetBSD: buildlink3.mk,v 1.3 2004/10/03 00:14:55 tv Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBART2_BUILDLINK3_MK:=	${LIBART2_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libart2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibart2}
BUILDLINK_PACKAGES+=	libart2

.if !empty(LIBART2_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libart2+=	libart2>=2.3.10nb1
BUILDLINK_RECOMMENDED.libart2+=	libart2>=2.3.16nb1
BUILDLINK_PKGSRCDIR.libart2?=	../../graphics/libart2
.endif	# LIBART2_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
