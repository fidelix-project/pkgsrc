# $NetBSD: buildlink3.mk,v 1.12 2004/03/10 17:57:15 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
XCURSOR_BUILDLINK3_MK:=	${XCURSOR_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	xcursor
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nxcursor}
BUILDLINK_PACKAGES+=	xcursor

.if !empty(XCURSOR_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.xcursor+=	xcursor>=1.0
BUILDLINK_PKGSRCDIR.xcursor?=	../../x11/xcursor

USE_X11=	yes

# Xfixes/buildlink3.mk is included by xcursor/builtin.mk
#.include "../../x11/Xfixes/buildlink3.mk"

.include "../../x11/Xrender/buildlink3.mk"

.endif	# XCURSOR_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
