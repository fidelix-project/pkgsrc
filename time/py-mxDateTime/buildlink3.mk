# $NetBSD: buildlink3.mk,v 1.3 2004/03/04 15:02:59 recht Exp $
#

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PY_MXDATETIME_BUILDLINK3_MK:=	${PY_MXDATETIME_BUILDLINK3_MK}+

.include "../../lang/python/pyversion.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	py-mxDateTime
.endif

.if !empty(PY_MXDATETIME_BUILDLINK3_MK:M+)
BUILDLINK_PACKAGES+=			py-mxDateTime
BUILDLINK_DEPENDS.py-mxDateTime+=		${PYPKGPREFIX}-mxDateTime>=2.0.5
BUILDLINK_PKGSRCDIR.py-mxDateTime?=		../../time/py-mxDateTime

BUILDLINK_INCDIRS.py-mxDateTime+=	${PYSITELIB}/mx/DateTime/mxDateTime

.endif # PY_MXDATETIME_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
