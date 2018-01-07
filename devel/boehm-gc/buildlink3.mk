# $NetBSD: buildlink3.mk,v 1.15 2018/01/07 13:04:00 rillig Exp $

BUILDLINK_TREE+=	boehm-gc

.if !defined(BOEHM_GC_BUILDLINK3_MK)
BOEHM_GC_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.boehm-gc+=	boehm-gc>=7.4
BUILDLINK_PKGSRCDIR.boehm-gc?=		../../devel/boehm-gc

.include "../../devel/libatomic_ops/buildlink3.mk"
.endif # BOEHM_GC_BUILDLINK3_MK

BUILDLINK_TREE+=	-boehm-gc
