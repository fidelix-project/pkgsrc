# $NetBSD: buildlink3.mk,v 1.23 2018/11/12 03:51:36 ryoon Exp $

BUILDLINK_TREE+=	qt5-qtsvg

.if !defined(QT5_QTSVG_BUILDLINK3_MK)
QT5_QTSVG_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.qt5-qtsvg+=	qt5-qtsvg>=5.9.1
BUILDLINK_ABI_DEPENDS.qt5-qtsvg+=	qt5-qtsvg>=5.11.2nb1
BUILDLINK_PKGSRCDIR.qt5-qtsvg?=	../../x11/qt5-qtsvg

BUILDLINK_INCDIRS.qt5-qtsvg+=	qt5/include
BUILDLINK_LIBDIRS.qt5-qtsvg+=	qt5/lib
BUILDLINK_LIBDIRS.qt5-qtsvg+=	qt5/plugins

.include "../../x11/qt5-qtbase/buildlink3.mk"
.endif	# QT5_QTSVG_BUILDLINK3_MK

BUILDLINK_TREE+=	-qt5-qtsvg
