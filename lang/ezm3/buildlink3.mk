# $NetBSD: buildlink3.mk,v 1.3 2006/04/06 06:22:10 reed Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
EZM3_BUILDLINK3_MK:=	${EZM3_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	ezm3
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nezm3}
BUILDLINK_PACKAGES+=	ezm3

.if !empty(EZM3_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.ezm3+=	ezm3>=1.1nb1
BUILDLINK_DEPMETHOD.ezm3?=	build
BUILDLINK_ABI_DEPENDS.ezm3?=	ezm3>=1.2nb1
BUILDLINK_PKGSRCDIR.ezm3?=	../../lang/ezm3
.endif	# EZM3_BUILDLINK3_MK

BUILDLINK_PASSTHRU_DIRS+=	${PREFIX}/ezm3

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
