# $NetBSD: buildlink3.mk,v 1.3 2006/04/06 06:23:02 reed Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PY_PMW_BUILDLINK3_MK:=	${PY_PMW_BUILDLINK3_MK}+

.include "../../lang/python/pyversion.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pypmw
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npypmw}
BUILDLINK_PACKAGES+=	pypmw

.if !empty(PY_PMW_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.pypmw+=	${PYPKGPREFIX}-Pmw-[0-9]*
BUILDLINK_ABI_DEPENDS.pypmw?=	${PYPKGPREFIX}-Pmw>=1.2nb1
BUILDLINK_PKGSRCDIR.pypmw?=	../../x11/py-Pmw
.endif	# PY_PMW_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
