# $NetBSD: buildlink3.mk,v 1.4 2012/02/06 12:39:57 wiz Exp $

BUILDLINK_TREE+=	qof

.if !defined(QOF_BUILDLINK3_MK)
QOF_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.qof+=	qof>=0.7.5
BUILDLINK_ABI_DEPENDS.qof?=	qof>=0.7.5nb8
BUILDLINK_PKGSRCDIR.qof?=	../../devel/qof

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.endif # QOF_BUILDLINK3_MK

BUILDLINK_TREE+=	-qof
