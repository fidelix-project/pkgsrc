# $NetBSD: buildlink3.mk,v 1.3 2016/08/03 10:22:25 adam Exp $

BUILDLINK_TREE+=	xfce4-garcon

.if !defined(XFCE4_GARCON_BUILDLINK3_MK)
XFCE4_GARCON_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xfce4-garcon+=	xfce4-garcon>=0.4.0
BUILDLINK_ABI_DEPENDS.xfce4-garcon?=	xfce4-garcon>=0.5.0nb1
BUILDLINK_PKGSRCDIR.xfce4-garcon?=	../../x11/xfce4-garcon

.include "../../x11/libxfce4ui/buildlink3.mk"
.endif	# XFCE4_GARCON_BUILDLINK3_MK

BUILDLINK_TREE+=	-xfce4-garcon
