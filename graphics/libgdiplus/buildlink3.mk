# $NetBSD: buildlink3.mk,v 1.36 2012/03/03 00:12:06 wiz Exp $

BUILDLINK_TREE+=	libgdiplus

.if !defined(LIBGDIPLUS_BUILDLINK3_MK)
LIBGDIPLUS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libgdiplus+=	libgdiplus>=2.8.1
BUILDLINK_ABI_DEPENDS.libgdiplus?=	libgdiplus>=2.10nb3
BUILDLINK_PKGSRCDIR.libgdiplus?=	../../graphics/libgdiplus

.include "../../devel/glib2/buildlink3.mk"
.include "../../graphics/cairo/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/giflib.buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.endif # LIBGDIPLUS_BUILDLINK3_MK

BUILDLINK_TREE+=	-libgdiplus
