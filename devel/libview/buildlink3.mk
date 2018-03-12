# $NetBSD: buildlink3.mk,v 1.26 2018/03/12 11:15:30 wiz Exp $

BUILDLINK_TREE+=	libview

.if !defined(LIBVIEW_BUILDLINK3_MK)
LIBVIEW_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libview+=	libview>=0.6.4
BUILDLINK_ABI_DEPENDS.libview+=	libview>=0.6.4nb24
BUILDLINK_PKGSRCDIR.libview?=	../../devel/libview

.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/gtkmm/buildlink3.mk"
.endif	# LIBVIEW_BUILDLINK3_MK

BUILDLINK_TREE+=	-libview
