# $NetBSD: buildlink3.mk,v 1.1.1.1 2007/02/18 14:18:18 xtraeme Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBRLOG_BUILDLINK3_MK:=	${LIBRLOG_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	librlog
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibrlog}
BUILDLINK_PACKAGES+=	librlog
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}librlog

.if ${LIBRLOG_BUILDLINK3_MK} == "+"
BUILDLINK_API_DEPENDS.librlog+=	librlog>=1.3.7
BUILDLINK_PKGSRCDIR.librlog?=	../../devel/librlog
.endif	# LIBRLOG_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
