# $NetBSD: buildlink3.mk,v 1.3 2006/05/23 11:17:33 rillig Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PY_CAIRO_BUILDLINK3_MK:=	${PY_CAIRO_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pycairo
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npycairo}
BUILDLINK_PACKAGES+=	pycairo

.if !empty(PY_CAIRO_BUILDLINK3_MK:M+)
.  include "../../lang/python/pyversion.mk"
BUILDLINK_API_DEPENDS.pycairo+=	${PYPKGPREFIX}-cairo>=1.0.2
BUILDLINK_ABI_DEPENDS.pycairo+=	${PYPKGPREFIX}-cairo>=1.0.2nb1
BUILDLINK_PKGSRCDIR.pycairo?=	../../graphics/py-cairo
.endif	# PY_CAIRO_BUILDLINK3_MK

.include "../../math/py-Numeric/buildlink3.mk"
.include "../../graphics/cairo/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
