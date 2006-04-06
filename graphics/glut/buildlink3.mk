# $NetBSD: buildlink3.mk,v 1.11 2006/04/06 06:22:02 reed Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
GLUT_BUILDLINK3_MK:=	${GLUT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	glut
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nglut}
BUILDLINK_PACKAGES+=	glut

.if !empty(GLUT_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.glut+=	glut>=3.4.2
BUILDLINK_ABI_DEPENDS.glut+=	glut>=6.4.1nb1
BUILDLINK_PKGSRCDIR.glut?=	../../graphics/glut
.endif	# GLUT_BUILDLINK3_MK

.include "../../graphics/MesaLib/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
