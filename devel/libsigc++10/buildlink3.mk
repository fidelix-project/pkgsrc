# $NetBSD: buildlink3.mk,v 1.2 2004/10/03 00:13:30 tv Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBSIGCXX10_BUILDLINK3_MK:=	${LIBSIGCXX10_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libsigcxx10
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibsigcxx10}
BUILDLINK_PACKAGES+=	libsigcxx10

.if !empty(LIBSIGCXX10_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.libsigcxx10+=	libsigc++10>=1.0.4nb1
BUILDLINK_RECOMMENDED.libsigcxx10+=	libsigc++10>=1.0.4nb2
BUILDLINK_PKGSRCDIR.libsigcxx10?=	../../devel/libsigc++10
.endif	# LIBSIGCXX10_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
