# $NetBSD: buildlink3.mk,v 1.4 2004/03/05 19:25:36 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PYTHON15_BUILDLINK3_MK:=	${PYTHON15_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	python15
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npython15}
BUILDLINK_PACKAGES+=	python15

.if !empty(PYTHON15_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.python15+=	python15>=1.5
BUILDLINK_PKGSRCDIR.python15?=	../../lang/python15

.if defined(BUILDLINK_DEPMETHOD.python)
BUILDLINK_DEPMETHOD.python15?=	${BUILDLINK_DEPMETHOD.python}
.endif

BUILDLINK_INCDIRS.python15+=	include/python1.5
BUILDLINK_LIBDIRS.python15+=	lib/python1.5/config
BUILDLINK_TRANSFORM+=		l:python:python1.5

.endif	# PYTHON15_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
