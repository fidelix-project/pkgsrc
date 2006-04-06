# $NetBSD: buildlink3.mk,v 1.3 2006/04/06 06:22:16 reed Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
DRAC_BUILDLINK3_MK:=	${DRAC_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	drac
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ndrac}
BUILDLINK_PACKAGES+=	drac

.if !empty(DRAC_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.drac+=	drac>=1.10
BUILDLINK_PKGSRCDIR.drac?=	../../mail/drac
BUILDLINK_DEPMETHOD.drac?=	build
.endif	# DRAC_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
