# $NetBSD: buildlink3.mk,v 1.5 2006/04/06 06:23:03 reed Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PYQT3_SIP_BUILDLINK3_MK:=	${PYQT3_SIP_BUILDLINK3_MK}+

.include "../../lang/python/pyversion.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pyqt3-sip
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npyqt3-sip}
BUILDLINK_PACKAGES+=	pyqt3-sip

.if !empty(PYQT3_SIP_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.pyqt3-sip+=	${PYPKGPREFIX}-qt3-sip>=4.0rc3
BUILDLINK_ABI_DEPENDS.pyqt3-sip?=	${PYPKGPREFIX}-qt3-sip>=4.3.2nb2
BUILDLINK_PKGSRCDIR.pyqt3-sip?=	../../x11/py-qt3-sip

BUILDLINK_LIBDIRS.pyqt3-sip+=	${PYSITELIB}
.endif	# PYQT3_SIP_BUILDLINK3_MK

SIPBIN=	${BUILDLINK_PREFIX.pyqt3-sip}/bin/sip${PYVERSSUFFIX}

.include "../../x11/qt3-libs/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
