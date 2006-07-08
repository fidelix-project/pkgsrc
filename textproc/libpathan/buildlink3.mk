# $NetBSD: buildlink3.mk,v 1.9 2006/07/08 22:39:41 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBPATHAN_BUILDLINK3_MK:=	${LIBPATHAN_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libpathan
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibpathan}
BUILDLINK_PACKAGES+=	libpathan
BUILDLINK_ORDER+=	libpathan

.if !empty(LIBPATHAN_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libpathan+=	libpathan>=1.2.2
BUILDLINK_ABI_DEPENDS.libpathan+=	libpathan>=1.2.2nb2
BUILDLINK_PKGSRCDIR.libpathan?=	../../textproc/libpathan
.endif	# LIBPATHAN_BUILDLINK3_MK

.include "../../textproc/xerces-c/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
