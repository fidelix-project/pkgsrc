# $NetBSD: buildlink3.mk,v 1.28 2012/09/07 19:17:35 adam Exp $

BUILDLINK_TREE+=	xfce4-xkb-plugin

.if !defined(XFCE4_XKB_PLUGIN_BUILDLINK3_MK)
XFCE4_XKB_PLUGIN_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-xkb-plugin+=	xfce4-xkb-plugin>=0.4.3
BUILDLINK_ABI_DEPENDS.xfce4-xkb-plugin+=	xfce4-xkb-plugin>=0.4.3nb11
BUILDLINK_PKGSRCDIR.xfce4-xkb-plugin?=	../../sysutils/xfce4-xkb-plugin

.include "../../x11/xfce4-panel/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.endif # XFCE4_XKB_PLUGIN_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-xkb-plugin
