# $NetBSD: buildlink3.mk,v 1.6 2013/06/04 22:17:04 tron Exp $

BUILDLINK_TREE+=	edbus

.if !defined(EDBUS_BUILDLINK3_MK)
EDBUS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.edbus+=	edbus>=1.1.0
BUILDLINK_ABI_DEPENDS.edbus?=	edbus>=1.1.0nb5
BUILDLINK_PKGSRCDIR.edbus?=	../../sysutils/edbus

.include "../../devel/ecore/buildlink3.mk"
.include "../../sysutils/dbus/buildlink3.mk"
.include "../../sysutils/efreet/buildlink3.mk"
.endif # EDBUS_BUILDLINK3_MK

BUILDLINK_TREE+=	-edbus
