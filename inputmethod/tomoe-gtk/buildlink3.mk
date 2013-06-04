# $NetBSD: buildlink3.mk,v 1.21 2013/06/04 22:16:33 tron Exp $

BUILDLINK_TREE+=	tomoe-gtk

.if !defined(TOMOE_GTK_BUILDLINK3_MK)
TOMOE_GTK_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.tomoe-gtk+=	tomoe-gtk>=0.6.0
BUILDLINK_ABI_DEPENDS.tomoe-gtk+=	tomoe-gtk>=0.6.0nb20
BUILDLINK_PKGSRCDIR.tomoe-gtk?=	../../inputmethod/tomoe-gtk

.include "../../inputmethod/tomoe/buildlink3.mk"
.include "../../fonts/gucharmap/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # TOMOE_GTK_BUILDLINK3_MK

BUILDLINK_TREE+=	-tomoe-gtk
