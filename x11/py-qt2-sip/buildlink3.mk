# $NetBSD: buildlink3.mk,v 1.5 2006/04/06 06:23:02 reed Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PY_QT2_SIP_BUILDLINK3_MK:=	${PY_QT2_SIP_BUILDLINK3_MK}+

.include "../../lang/python/pyversion.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pyqt2sip
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npyqt2sip}
BUILDLINK_PACKAGES+=	pyqt2sip

.if !empty(PY_QT2_SIP_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.pyqt2sip+=	${PYPKGPREFIX}-qt2-sip-[0-9]*
BUILDLINK_ABI_DEPENDS.pyqt2sip+=	${PYPKGPREFIX}-qt2-sip>=3.1nb3
BUILDLINK_PKGSRCDIR.pyqt2sip?=	../../x11/py-qt2-sip
.endif	# PY_QT2_SIP_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
