# $NetBSD: buildlink3.mk,v 1.1 2004/04/25 17:10:19 snj Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
HDF_BUILDLINK3_MK:=	${HDF_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	hdf
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nhdf}
BUILDLINK_PACKAGES+=	hdf

.if !empty(HDF_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.hdf+=	hdf>=4.1r5
BUILDLINK_PKGSRCDIR.hdf?=	../../devel/hdf
.endif	# HDF_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
