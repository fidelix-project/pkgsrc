# $NetBSD: buildlink3.mk,v 1.4 2009/03/20 19:24:29 joerg Exp $

BUILDLINK_TREE+=	sgb

.if !defined(SGB_BUILDLINK3_MK)
SGB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.sgb+=	sgb>=0pre20050409
BUILDLINK_PKGSRCDIR.sgb?=	../../devel/sgb
.endif # SGB_BUILDLINK3_MK

BUILDLINK_TREE+=	-sgb
