# $NetBSD: buildlink3.mk,v 1.1 2004/05/08 06:41:33 snj Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PWLIB_BUILDLINK3_MK:=	${PWLIB_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pwlib
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npwlib}
BUILDLINK_PACKAGES+=	pwlib

.if !empty(PWLIB_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.pwlib+=	pwlib>=1.4.4nb3
BUILDLINK_PKGSRCDIR.pwlib?=	../../devel/pwlib
.endif	# PWLIB_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
