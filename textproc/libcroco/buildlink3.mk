# $NetBSD: buildlink3.mk,v 1.28 2015/11/23 12:37:46 szptvlfn Exp $

BUILDLINK_TREE+=	libcroco

.if !defined(LIBCROCO_BUILDLINK3_MK)
LIBCROCO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libcroco+=	libcroco>=0.6.0
BUILDLINK_ABI_DEPENDS.libcroco+=	libcroco>=0.6.5nb2
BUILDLINK_PKGSRCDIR.libcroco?=	../../textproc/libcroco

.include "../../archivers/lzmalib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.endif # LIBCROCO_BUILDLINK3_MK

BUILDLINK_TREE+=	-libcroco
