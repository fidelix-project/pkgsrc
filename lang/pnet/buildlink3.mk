# $NetBSD: buildlink3.mk,v 1.3 2004/03/11 08:06:56 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PNET_BUILDLINK3_MK:=	${PNET_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pnet
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npnet}
BUILDLINK_PACKAGES+=	pnet

.if !empty(PNET_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.pnet+=	pnet>=0.6.2
BUILDLINK_PKGSRCDIR.pnet?=	../../lang/pnet

.include "../../devel/zlib/buildlink3.mk"

.endif	# PNET_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
