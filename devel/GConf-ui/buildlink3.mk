# $NetBSD: buildlink3.mk,v 1.11 2012/03/03 00:12:25 wiz Exp $

BUILDLINK_TREE+=	GConf-ui

.if !defined(GCONF_UI_BUILDLINK3_MK)
GCONF_UI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.GConf-ui+=	GConf-ui>=2.8.0.1
BUILDLINK_ABI_DEPENDS.GConf-ui?=	GConf-ui>=2.32.4nb2
BUILDLINK_PKGSRCDIR.GConf-ui?=	../../devel/GConf-ui

.include "../../devel/GConf/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # GCONF_UI_BUILDLINK3_MK

BUILDLINK_TREE+=	-GConf-ui
