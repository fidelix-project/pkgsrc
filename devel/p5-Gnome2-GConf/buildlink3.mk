# $NetBSD: buildlink3.mk,v 1.3 2012/02/06 12:39:56 wiz Exp $

BUILDLINK_TREE+=	p5-Gnome2-GConf

.if !defined(P5_GNOME2_GCONF_BUILDLINK3_MK)
P5_GNOME2_GCONF_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.p5-Gnome2-GConf+=	p5-Gnome2-GConf>=1.044
BUILDLINK_ABI_DEPENDS.p5-Gnome2-GConf?=	p5-Gnome2-GConf>=1.044nb3
BUILDLINK_PKGSRCDIR.p5-Gnome2-GConf?=	../../devel/p5-Gnome2-GConf

.include "../../devel/GConf/buildlink3.mk"
.include "../../devel/p5-glib2/buildlink3.mk"
.endif # P5_GNOME2_GCONF_BUILDLINK3_MK

BUILDLINK_TREE+=	-p5-Gnome2-GConf
