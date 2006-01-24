# $NetBSD: buildlink3.mk,v 1.3 2006/01/24 07:32:59 wiz Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
QT2_DESIGNER_BUILDLINK3_MK:=	${QT2_DESIGNER_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	qt2-designer
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nqt2-designer}
BUILDLINK_PACKAGES+=	qt2-designer

.if !empty(QT2_DESIGNER_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.qt2-designer+=	qt2-designer>=2.3.1nb2
BUILDLINK_RECOMMENDED.qt2-designer+=	qt2-designer>=2.3.1nb4
BUILDLINK_PKGSRCDIR.qt2-designer?=	../../x11/qt2-designer
.endif	# QT2_DESIGNER_BUILDLINK3_MK

.include "../../x11/qt2-libs/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
