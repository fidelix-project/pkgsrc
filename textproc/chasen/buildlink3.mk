# $NetBSD: buildlink3.mk,v 1.1 2004/05/05 00:28:50 snj Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
CHASEN_BUILDLINK3_MK:=	${CHASEN_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	chasen
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nchasen}
BUILDLINK_PACKAGES+=	chasen

.if !empty(CHASEN_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.chasen+=	chasen>=2.0
BUILDLINK_PKGSRCDIR.chasen?=	../../textproc/chasen
BUILDLINK_FILES.chasen=		include/chasen.h
BUILDLINK_FILES.chasen+=	lib/libchasen.*
.endif	# CHASEN_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
