# $NetBSD: buildlink3.mk,v 1.33 2018/03/12 11:15:42 wiz Exp $

BUILDLINK_TREE+=	libgnomecups

.if !defined(LIBGNOMECUPS_BUILDLINK3_MK)
LIBGNOMECUPS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libgnomecups+=	libgnomecups>=0.2.0
BUILDLINK_ABI_DEPENDS.libgnomecups+=	libgnomecups>=0.2.3nb21
BUILDLINK_PKGSRCDIR.libgnomecups?=	../../print/libgnomecups

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../print/cups-base/buildlink3.mk"
.endif # LIBGNOMECUPS_BUILDLINK3_MK

BUILDLINK_TREE+=	-libgnomecups
