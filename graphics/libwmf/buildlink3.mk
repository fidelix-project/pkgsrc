# $NetBSD: buildlink3.mk,v 1.22 2011/11/01 06:01:41 sbd Exp $

BUILDLINK_TREE+=	libwmf

.if !defined(LIBWMF_BUILDLINK3_MK)
LIBWMF_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libwmf+=	libwmf>=0.2.8nb2
BUILDLINK_ABI_DEPENDS.libwmf+=	libwmf>=0.2.8.4nb10
BUILDLINK_PKGSRCDIR.libwmf?=	../../graphics/libwmf

pkgbase:= libwmf
.include "../../mk/pkg-build-options.mk"
.if !empty(PKG_BUILD_OPTIONS.libwmf:Mx11)
.include "../../x11/libX11/buildlink3.mk"
.endif

.include "../../graphics/freetype2/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.endif # LIBWMF_BUILDLINK3_MK

BUILDLINK_TREE+=	-libwmf
