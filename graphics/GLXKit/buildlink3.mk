# $NetBSD: buildlink3.mk,v 1.2 2004/09/24 01:56:54 rh Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
GLXKIT_BUILDLINK3_MK:=	${GLXKIT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	GLXKit
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:NGLXKit}
BUILDLINK_PACKAGES+=	GLXKit

.if !empty(GLXKIT_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.GLXKit+=	GLXKit>=0.3.1r2nb3
BUILDLINK_RECOMMENDED.GLXKit?=	GLXKit>=0.3.1r2nb6
BUILDLINK_PKGSRCDIR.GLXKit?=	../../graphics/GLXKit
.endif	# GLXKIT_BUILDLINK3_MK

.include "../../graphics/RenderKit/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
