# $NetBSD: buildlink3.mk,v 1.2 2004/03/05 19:25:40 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
FAM_BUILDLINK3_MK:=	${FAM_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	fam
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nfam}
BUILDLINK_PACKAGES+=	fam

.if !empty(FAM_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.fam+=		fam>=2.6.10
BUILDLINK_PKGSRCDIR.fam?=	../../sysutils/fam
.endif	# FAM_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
