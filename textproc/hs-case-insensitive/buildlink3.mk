# $NetBSD: buildlink3.mk,v 1.2 2014/09/13 22:06:12 szptvlfn Exp $

BUILDLINK_TREE+=	hs-case-insensitive

.if !defined(HS_CASE_INSENSITIVE_BUILDLINK3_MK)
HS_CASE_INSENSITIVE_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-case-insensitive+=	hs-case-insensitive>=1.2.0
BUILDLINK_ABI_DEPENDS.hs-case-insensitive+=	hs-case-insensitive>=1.2.0.1
BUILDLINK_PKGSRCDIR.hs-case-insensitive?=	../../textproc/hs-case-insensitive

.include "../../devel/hs-hashable/buildlink3.mk"
.include "../../devel/hs-text/buildlink3.mk"
.endif	# HS_CASE_INSENSITIVE_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-case-insensitive
