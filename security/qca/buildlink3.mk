# $NetBSD: buildlink3.mk,v 1.7 2006/07/08 22:39:38 jlam Exp $
# 
BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
QCA_BUILDLINK3_MK:=	${QCA_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	qca
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nqca}
BUILDLINK_PACKAGES+=	qca
BUILDLINK_ORDER+=	qca

.if !empty(QCA_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.qca+=	qca>=1.0
BUILDLINK_ABI_DEPENDS.qca?=	qca>=1.0nb3
BUILDLINK_PKGSRCDIR.qca?=	../../security/qca
.endif	# QCA_BUILDLINK3_MK

.include "../../x11/qt3-libs/buildlink3.mk"
.include "../../x11/qt3-tools/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
