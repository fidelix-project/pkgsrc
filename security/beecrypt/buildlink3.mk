# $NetBSD: buildlink3.mk,v 1.5 2006/07/08 22:39:36 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
BEECRYPT_BUILDLINK3_MK:=	${BEECRYPT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	beecrypt
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nbeecrypt}
BUILDLINK_PACKAGES+=	beecrypt
BUILDLINK_ORDER+=	beecrypt

.if !empty(BEECRYPT_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.beecrypt+=	beecrypt>=3.0.0
BUILDLINK_ABI_DEPENDS.beecrypt+=	beecrypt>=3.0.0nb1
BUILDLINK_PKGSRCDIR.beecrypt?=	../../security/beecrypt
.endif	# BEECRYPT_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
