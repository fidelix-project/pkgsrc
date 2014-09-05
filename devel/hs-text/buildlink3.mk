# $NetBSD: buildlink3.mk,v 1.3 2014/09/05 21:23:59 szptvlfn Exp $

BUILDLINK_TREE+=	hs-text

.if !defined(HS_TEXT_BUILDLINK3_MK)
HS_TEXT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-text+=	hs-text>=1.1.1
BUILDLINK_ABI_DEPENDS.hs-text+=	hs-text>=1.1.1.3
BUILDLINK_PKGSRCDIR.hs-text?=	../../devel/hs-text
.endif	# HS_TEXT_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-text
