# $NetBSD: buildlink3.mk,v 1.5 2017/01/01 16:06:01 adam Exp $

BUILDLINK_TREE+=	elementary

.if !defined(ELEMENTARY_BUILDLINK3_MK)
ELEMENTARY_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.elementary+=	elementary>=1.7.7
BUILDLINK_ABI_DEPENDS.elementary?=	elementary>=1.7.7nb7
BUILDLINK_PKGSRCDIR.elementary?=	../../x11/elementary

.include "../../devel/ecore/buildlink3.mk"
.include "../../graphics/edje/buildlink3.mk"
.include "../../sysutils/edbus/buildlink3.mk"
.include "../../sysutils/efreet/buildlink3.mk"
.include "../../devel/eet/buildlink3.mk"
.include "../../graphics/evas-png/buildlink3.mk"
.include "../../graphics/evas-jpeg/buildlink3.mk"
.include "../../graphics/evas/buildlink3.mk"
.include "../../devel/eio/buildlink3.mk"
.endif	# ELEMENTARY_BUILDLINK3_MK

BUILDLINK_TREE+=	-elementary
