# $NetBSD: buildlink3.mk,v 1.2 2004/02/08 16:21:44 tron Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBMAD_BUILDLINK3_MK:=		${LIBMAD_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libmad
.endif

.if !empty(LIBMAD_BUILDLINK3_MK:M+)
BUILDLINK_PACKAGES+=		libmad
BUILDLINK_DEPENDS.libmad+=	libmad>=0.15.0bnb1
BUILDLINK_PKGSRCDIR.libmad?=	../../audio/libmad
.endif	# LIBMAD_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
