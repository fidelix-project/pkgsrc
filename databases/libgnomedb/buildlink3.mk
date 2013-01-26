# $NetBSD: buildlink3.mk,v 1.42 2013/01/26 21:36:15 adam Exp $

BUILDLINK_TREE+=	libgnomedb

.if !defined(LIBGNOMEDB_BUILDLINK3_MK)
LIBGNOMEDB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libgnomedb+=	libgnomedb>=2.99.2
BUILDLINK_ABI_DEPENDS.libgnomedb+=	libgnomedb>=3.0.0nb21
BUILDLINK_PKGSRCDIR.libgnomedb?=	../../databases/libgnomedb

.include "../../databases/libgda/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/libglade/buildlink3.mk"
.include "../../graphics/libgnomecanvas/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/gtksourceview/buildlink3.mk"
.endif # LIBGNOMEDB_BUILDLINK3_MK

BUILDLINK_TREE+=	-libgnomedb
