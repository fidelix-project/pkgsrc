# $NetBSD: buildlink3.mk,v 1.1 2004/01/03 23:06:43 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
DLCOMPAT_BUILDLINK3_MK:=	${DLCOMPAT_BUILDLINK3_MK}+

.if !empty(DLCOMPAT_BUILDLINK3_MK:M\+)
BUILDLINK_DEPENDS.dlcompat?=	dlcompat>=20020606
BUILDLINK_PKGSRCDIR.dlcompat?=	../../devel/dlcompat
.endif  # DLCOMPAT_BUILDLINK3_MK

.if !empty(BUILDLINK_DEPTH:M\+)
BUILDLINK_DEPENDS+=	dlcompat
.endif

.if !empty(DLCOMPAT_BUILDLINK3_MK:M\+)
BUILDLINK_PACKAGES+=	dlcompat
.endif  # DLCOMPAT_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:C/\+$//}
