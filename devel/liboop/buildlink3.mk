# $NetBSD: buildlink3.mk,v 1.1 2004/04/25 03:47:44 snj Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBOOP_BUILDLINK3_MK:=	${LIBOOP_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	liboop
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nliboop}
BUILDLINK_PACKAGES+=	liboop

.if !empty(LIBOOP_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.liboop+=	liboop>=0.9
BUILDLINK_PKGSRCDIR.liboop?=	../../devel/liboop
.endif	# LIBOOP_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
