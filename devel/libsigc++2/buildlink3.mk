# $NetBSD: buildlink3.mk,v 1.2 2004/10/03 00:13:30 tv Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBSIGC++_BUILDLINK3_MK:=	${LIBSIGC++_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libsigcxx
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibsigcxx}
BUILDLINK_PACKAGES+=	libsigcxx

.if !empty(LIBSIGC++_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libsigcxx+=	libsigc++2>=2.0.3
BUILDLINK_RECOMMENDED.libsigcxx+=	libsigc++2>=2.0.3nb1
BUILDLINK_PKGSRCDIR.libsigcxx?=	../../devel/libsigc++2
.endif	# LIBSIGC++_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
