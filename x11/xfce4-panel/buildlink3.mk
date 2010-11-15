# $NetBSD: buildlink3.mk,v 1.28 2010/11/15 22:59:17 abs Exp $

BUILDLINK_TREE+=	xfce4-panel

.if !defined(XFCE4_PANEL_BUILDLINK3_MK)
XFCE4_PANEL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-panel+=	xfce4-panel>=4.6.0
BUILDLINK_ABI_DEPENDS.xfce4-panel?=	xfce4-panel>=4.6.2nb4
BUILDLINK_PKGSRCDIR.xfce4-panel?=	../../x11/xfce4-panel

.include "../../devel/glib2/buildlink3.mk"
.include "../../x11/libxfce4gui/buildlink3.mk"
.include "../../x11/libxfce4util/buildlink3.mk"
.endif # XFCE4_PANEL_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-panel
