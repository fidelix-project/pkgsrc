# $NetBSD: buildlink3.mk,v 1.11 2018/04/29 21:31:18 adam Exp $

BUILDLINK_TREE+=	libe-book

.if !defined(LIBE_BOOK_BUILDLINK3_MK)
LIBE_BOOK_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libe-book+=	libe-book>=0.0.2
BUILDLINK_ABI_DEPENDS.libe-book?=	libe-book>=0.1.3nb2
BUILDLINK_PKGSRCDIR.libe-book?=		../../converters/libe-book

.include "../../converters/librevenge/buildlink3.mk"
.include "../../converters/libwpd/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.endif	# LIBE_BOOK_BUILDLINK3_MK

BUILDLINK_TREE+=	-libe-book
