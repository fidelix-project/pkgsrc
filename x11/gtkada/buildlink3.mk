# $NetBSD: buildlink3.mk,v 1.25 2018/11/12 03:51:30 ryoon Exp $

BUILDLINK_TREE+=	gtkada

.if !defined(GTKADA_BUILDLINK3_MK)
GTKADA_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gtkada+=	gtkada>=2.22
BUILDLINK_ABI_DEPENDS.gtkada+=	gtkada>=2.24.4.0nb18
BUILDLINK_PKGSRCDIR.gtkada?=	../../x11/gtkada

.include "../../x11/gtk2/buildlink3.mk"
.endif	# GTKADA_BUILDLINK3_MK

BUILDLINK_TREE+=	-gtkada
