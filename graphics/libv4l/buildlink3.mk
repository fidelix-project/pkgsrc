# $NetBSD: buildlink3.mk,v 1.1.1.1 2008/09/08 19:07:41 jmcneill Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBV4L_BUILDLINK3_MK:=		${LIBV4L_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libv4l
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibv4l}
BUILDLINK_PACKAGES+=	libv4l
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}libv4l

.if !empty(LIBV4L_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libv4l+=		libv4l>=0.4.3
BUILDLINK_ABI_DEPENDS.libv4l+=		libv4l>=0.4.3
BUILDLINK_PKGSRCDIR.libv4l?=		../../graphics/libv4l
.endif	# LIBV4L_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
