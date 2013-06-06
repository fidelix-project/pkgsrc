# $NetBSD: buildlink3.mk,v 1.35 2013/06/06 12:54:00 wiz Exp $

BUILDLINK_TREE+=	xfce4-diskperf-plugin

.if !defined(XFCE4_DISKPERF_PLUGIN_BUILDLINK3_MK)
XFCE4_DISKPERF_PLUGIN_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-diskperf-plugin+=	xfce4-diskperf-plugin>=2.1.0
BUILDLINK_ABI_DEPENDS.xfce4-diskperf-plugin+=	xfce4-diskperf-plugin>=2.1.0nb18
BUILDLINK_PKGSRCDIR.xfce4-diskperf-plugin?=	../../sysutils/xfce4-diskperf-plugin

.include "../../x11/xfce4-panel/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.endif # XFCE4_DISKPERF_PLUGIN_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-diskperf-plugin
