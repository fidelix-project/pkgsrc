# $NetBSD: buildlink3.mk,v 1.30 2015/04/21 08:56:43 jperkin Exp $

BUILDLINK_TREE+=	libxfce4util

.if !defined(LIBXFCE4UTIL_BUILDLINK3_MK)
LIBXFCE4UTIL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libxfce4util+=	libxfce4util>=4.12.0
BUILDLINK_ABI_DEPENDS.libxfce4util+=	libxfce4util>=4.12.0
BUILDLINK_PKGSRCDIR.libxfce4util?=	../../x11/libxfce4util

.include "../../x11/gtk2/buildlink3.mk"
.endif # LIBXFCE4UTIL_BUILDLINK3_MK

BUILDLINK_TREE+=	-libxfce4util
