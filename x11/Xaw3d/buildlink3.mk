# $NetBSD: buildlink3.mk,v 1.3 2005/06/01 18:03:27 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
XAW3D_BUILDLINK3_MK:=	${XAW3D_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	Xaw3d
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:NXaw3d}
BUILDLINK_PACKAGES+=	Xaw3d

.if !empty(XAW3D_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.Xaw3d+=	Xaw3d>=1.5
BUILDLINK_PKGSRCDIR.Xaw3d?=	../../x11/Xaw3d
.endif	# XAW3D_BUILDLINK3_MK

.include "../../mk/bsd.prefs.mk"
.include "../../mk/x11.buildlink3.mk"

LIBXAW?=	-L${BUILDLINK_PREFIX.Xaw3d}/lib				\
		${COMPILER_RPATH_FLAG}${BUILDLINK_PREFIX.Xaw3d}/lib	\
		-lXaw3d

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
