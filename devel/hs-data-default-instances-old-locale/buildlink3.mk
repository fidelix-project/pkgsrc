# $NetBSD: buildlink3.mk,v 1.1 2014/05/19 21:25:16 szptvlfn Exp $

BUILDLINK_TREE+=	hs-data-default-instances-old-locale

.if !defined(HS_DATA_DEFAULT_INSTANCES_OLD_LOCALE_BUILDLINK3_MK)
HS_DATA_DEFAULT_INSTANCES_OLD_LOCALE_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.hs-data-default-instances-old-locale+=	hs-data-default-instances-old-locale>=0.0.1
BUILDLINK_PKGSRCDIR.hs-data-default-instances-old-locale?=	../../devel/hs-data-default-instances-old-locale

.include "../../devel/hs-data-default-class/buildlink3.mk"
.endif	# HS_DATA_DEFAULT_INSTANCES_OLD_LOCALE_BUILDLINK3_MK

BUILDLINK_TREE+=	-hs-data-default-instances-old-locale
