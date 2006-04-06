# $NetBSD: buildlink3.mk,v 1.8 2006/04/06 06:21:48 reed Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
DEVIL_BUILDLINK3_MK:=	${DEVIL_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	devIL
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:NdevIL}
BUILDLINK_PACKAGES+=	devIL

.if !empty(DEVIL_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.devIL+=	devIL>=1.6.6nb1
BUILDLINK_ABI_DEPENDS.devIL+=	devIL>=1.6.6nb6
BUILDLINK_PKGSRCDIR.devIL?=	../../devel/devIL
.endif	# DEVIL_BUILDLINK3_MK

.include "../../devel/SDL/buildlink3.mk"
.include "../../graphics/jpeg/buildlink3.mk"
.include "../../graphics/libungif/buildlink3.mk"
.include "../../graphics/mng/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../graphics/xpm/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
