# $NetBSD: buildlink3.mk,v 1.38 2012/09/07 19:17:49 adam Exp $

BUILDLINK_TREE+=	libxfce4gui

.if !defined(LIBXFCE4GUI_BUILDLINK3_MK)
LIBXFCE4GUI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libxfce4gui+=	libxfce4gui>=4.6.0
BUILDLINK_ABI_DEPENDS.libxfce4gui+=	libxfce4gui>=4.6.1nb11
BUILDLINK_PKGSRCDIR.libxfce4gui?=	../../x11/libxfce4gui

.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/xfconf/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/libxfce4util/buildlink3.mk"
.include "../../x11/startup-notification/buildlink3.mk"
.endif # LIBXFCE4GUI_BUILDLINK3_MK

BUILDLINK_TREE+=	-libxfce4gui
