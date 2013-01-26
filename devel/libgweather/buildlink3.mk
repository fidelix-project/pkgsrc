# $NetBSD: buildlink3.mk,v 1.22 2013/01/26 21:36:21 adam Exp $

BUILDLINK_TREE+=	libgweather

.if !defined(LIBGWEATHER_BUILDLINK3_MK)
LIBGWEATHER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libgweather+=	libgweather>=2.22.0
BUILDLINK_ABI_DEPENDS.libgweather+=	libgweather>=2.30.3nb14
BUILDLINK_PKGSRCDIR.libgweather?=	../../devel/libgweather

.include "../../net/libsoup24/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # LIBGWEATHER_BUILDLINK3_MK

BUILDLINK_TREE+=	-libgweather
