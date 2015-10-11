# $NetBSD: buildlink3.mk,v 1.23 2015/10/11 10:41:37 tron Exp $

BUILDLINK_TREE+=	libtorrent

.if !defined(LIBTORRENT_BUILDLINK3_MK)
LIBTORRENT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libtorrent+=	libtorrent>=0.13.6
BUILDLINK_ABI_DEPENDS.libtorrent+=	libtorrent>=0.13.6
BUILDLINK_PKGSRCDIR.libtorrent?=	../../net/libtorrent

.include "../../devel/libsigc++/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.endif # LIBTORRENT_BUILDLINK3_MK

BUILDLINK_TREE+=	-libtorrent
