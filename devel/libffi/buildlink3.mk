# $NetBSD: buildlink3.mk,v 1.2 2004/10/03 00:13:29 tv Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LIBFFI_BUILDLINK3_MK:=	${LIBFFI_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libffi
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibffi}
BUILDLINK_PACKAGES+=	libffi

.if !empty(LIBFFI_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libffi+=	libffi>=1.20
BUILDLINK_RECOMMENDED.libffi+=	libffi>=2.0betanb1
BUILDLINK_PKGSRCDIR.libffi?=	../../devel/libffi
.endif	# LIBFFI_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
