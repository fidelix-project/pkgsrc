# $NetBSD: buildlink3.mk,v 1.2 2004/03/05 19:25:38 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
GNET_BUILDLINK3_MK:=	${GNET_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	gnet
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ngnet}
BUILDLINK_PACKAGES+=	gnet

.if !empty(GNET_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.gnet+=	gnet>=2.0.3nb1
BUILDLINK_PKGSRCDIR.gnet?=	../../net/gnet

.include "../../devel/glib2/buildlink3.mk"

.endif	# GNET_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
