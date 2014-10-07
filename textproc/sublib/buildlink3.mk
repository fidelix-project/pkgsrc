# $NetBSD: buildlink3.mk,v 1.13 2014/10/07 16:47:14 adam Exp $

BUILDLINK_TREE+=	sublib

.if !defined(SUBLIB_BUILDLINK3_MK)
SUBLIB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.sublib+=	sublib>=0.9
BUILDLINK_ABI_DEPENDS.sublib+=	sublib>=0.9nb11
BUILDLINK_PKGSRCDIR.sublib?=	../../textproc/sublib

.include "../../lang/mono2/buildlink3.mk"
.endif # SUBLIB_BUILDLINK3_MK

BUILDLINK_TREE+=	-sublib
