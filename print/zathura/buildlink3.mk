# $NetBSD: buildlink3.mk,v 1.8 2018/11/12 03:51:23 ryoon Exp $

BUILDLINK_TREE+=	zathura

.if !defined(ZATHURA_BUILDLINK3_MK)
ZATHURA_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.zathura+=	zathura>=0.2.1
BUILDLINK_ABI_DEPENDS.zathura+=	zathura>=0.4.1nb1
BUILDLINK_PKGSRCDIR.zathura?=	../../print/zathura

.include "../../graphics/cairo/buildlink3.mk"
.include "../../graphics/girara/buildlink3.mk"
.endif # ZATHURA_BUILDLINK3_MK

BUILDLINK_TREE+=	-zathura
