# $NetBSD: buildlink3.mk,v 1.13 2006/04/06 06:23:02 reed Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
LIBXFCE4MCS_BUILDLINK3_MK:=	${LIBXFCE4MCS_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	libxfce4mcs
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlibxfce4mcs}
BUILDLINK_PACKAGES+=	libxfce4mcs

.if !empty(LIBXFCE4MCS_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.libxfce4mcs+=	libxfce4mcs>=4.2.3
BUILDLINK_ABI_DEPENDS.libxfce4mcs?=	libxfce4mcs>=4.2.3nb1
BUILDLINK_PKGSRCDIR.libxfce4mcs?=	../../x11/libxfce4mcs
.endif	# LIBXFCE4MCS_BUILDLINK3_MK

.include "../../x11/libxfce4util/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
