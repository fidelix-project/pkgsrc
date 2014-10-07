# $NetBSD: buildlink3.mk,v 1.5 2014/10/07 16:47:14 adam Exp $

BUILDLINK_TREE+=	dbus-sharp

.if !defined(DBUS_SHARP_BUILDLINK3_MK)
DBUS_SHARP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.dbus-sharp+=	dbus-sharp>=0.7.0
BUILDLINK_ABI_DEPENDS.dbus-sharp?=	dbus-sharp>=0.7.0nb5
BUILDLINK_PKGSRCDIR.dbus-sharp?=	../../sysutils/dbus-sharp

.include "../../lang/mono2/buildlink3.mk"
.endif	# DBUS_SHARP_BUILDLINK3_MK

BUILDLINK_TREE+=	-dbus-sharp
