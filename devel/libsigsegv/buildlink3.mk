# $NetBSD: buildlink3.mk,v 1.4 2006/07/08 22:39:12 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBSIGSEGV_BUILDLINK3_MK:=	${LIBSIGSEGV_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libsigsegv
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibsigsegv}
BUILDLINK_PACKAGES+=	libsigsegv
BUILDLINK_ORDER+=	libsigsegv

.if !empty(LIBSIGSEGV_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libsigsegv+=	libsigsegv>=2.2
BUILDLINK_PKGSRCDIR.libsigsegv?=	../../devel/libsigsegv
# only installs a static library
BUILDLINK_DEPMETHOD.libsigsegv?=	build
.endif	# LIBSIGSEGV_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
