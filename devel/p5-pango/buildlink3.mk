# $NetBSD: buildlink3.mk,v 1.7 2012/02/06 12:39:56 wiz Exp $

BUILDLINK_TREE+=	p5-pango

.if !defined(P5_PANGO_BUILDLINK3_MK)
P5_PANGO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.p5-pango+=	p5-pango>=1.200
BUILDLINK_ABI_DEPENDS.p5-pango?=		p5-pango>=1.222nb2
BUILDLINK_PKGSRCDIR.p5-pango?=		../../devel/p5-pango

.include "../../devel/pango/buildlink3.mk"
.endif # P5_PANGO_BUILDLINK3_MK

BUILDLINK_TREE+=	-p5-pango
