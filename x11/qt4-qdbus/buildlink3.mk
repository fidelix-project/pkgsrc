# $NetBSD: buildlink3.mk,v 1.28 2018/01/07 13:04:41 rillig Exp $

BUILDLINK_TREE+=	qt4-qdbus

.if !defined(QT4_QDBUS_BUILDLINK3_MK)
QT4_QDBUS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.qt4-qdbus+=	qt4-qdbus>=4.3.2
BUILDLINK_ABI_DEPENDS.qt4-qdbus+=	qt4-qdbus>=4.8.7nb1
BUILDLINK_PKGSRCDIR.qt4-qdbus?=		../../x11/qt4-qdbus

.include "../../x11/qt4-libs/buildlink3.mk"
.include "../../sysutils/dbus/buildlink3.mk"
.endif # QT4_QDBUS_BUILDLINK3_MK

BUILDLINK_TREE+=	-qt4-qdbus
