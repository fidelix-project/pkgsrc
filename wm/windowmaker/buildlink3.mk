# $NetBSD: buildlink3.mk,v 1.5 2004/11/05 11:51:35 adam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
WINDOWMAKER_BUILDLINK3_MK:=	${WINDOWMAKER_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	windowmaker
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nwindowmaker}
BUILDLINK_PACKAGES+=	windowmaker

.if !empty(WINDOWMAKER_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.windowmaker+=		windowmaker>=0.80.2nb3
BUILDLINK_RECOMMENDED.windowmaker+=	windowmaker>=0.91.0
BUILDLINK_PKGSRCDIR.windowmaker?=	../../wm/windowmaker
.endif	# WINDOWMAKER_BUILDLINK3_MK

.include "../../fonts/Xft2/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../graphics/hermes/buildlink3.mk"
.include "../../graphics/jpeg/buildlink3.mk"
.include "../../graphics/libungif/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../graphics/xpm/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
