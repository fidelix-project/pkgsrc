# $NetBSD: buildlink3.mk,v 1.3 2004/10/03 00:14:39 tv Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PICO_BUILDLINK3_MK:=	${PICO_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pico
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npico}
BUILDLINK_PACKAGES+=	pico

.if !empty(PICO_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.pico+=	pico>=4.7
BUILDLINK_RECOMMENDED.pico+=	pico>=4.8nb1
BUILDLINK_PKGSRCDIR.pico?=	../../editors/pico
.endif	# PICO_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
