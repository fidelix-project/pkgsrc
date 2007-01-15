# $NetBSD: buildlink3.mk,v 1.2 2007/01/15 03:03:47 rillig Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PY_MUTAGEN_BUILDLINK3_MK:=	${PY_MUTAGEN_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	py-mutagen
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npy-mutagen}
BUILDLINK_PACKAGES+=	py-mutagen
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}py-mutagen

.if ${PY_MUTAGEN_BUILDLINK3_MK} == "+"
.  include "../../lang/python/pyversion.mk"
BUILDLINK_API_DEPENDS.py-mutagen+=	${PYPKGPREFIX}-mutagen>=1.9
BUILDLINK_PKGSRCDIR.py-mutagen?=	../../audio/py-mutagen
.endif	# PY_MUTAGEN_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
