# $NetBSD: buildlink3.mk,v 1.24 2015/04/25 14:23:46 tnn Exp $

BUILDLINK_TREE+=	libktorrent

.if !defined(LIBKTORRENT_BUILDLINK3_MK)
LIBKTORRENT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libktorrent+=	libktorrent>=1.2.1.2
BUILDLINK_ABI_DEPENDS.libktorrent+=	libktorrent>=1.3.1nb2
BUILDLINK_PKGSRCDIR.libktorrent?=	../../net/libktorrent

.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/gmp/buildlink3.mk"
.include "../../security/qca2/buildlink3.mk"
.include "../../x11/kdelibs4/buildlink3.mk"
.endif # LIBTORRENT_BUILDLINK3_MK

BUILDLINK_TREE+=	-libktorrent
