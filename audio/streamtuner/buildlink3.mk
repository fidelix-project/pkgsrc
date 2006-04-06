# $NetBSD: buildlink3.mk,v 1.6 2006/04/06 06:21:37 reed Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
STREAMTUNER_BUILDLINK3_MK:=	${STREAMTUNER_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	streamtuner
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nstreamtuner}
BUILDLINK_PACKAGES+=	streamtuner

.if !empty(STREAMTUNER_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.streamtuner+=		streamtuner>=0.99
BUILDLINK_ABI_DEPENDS.streamtuner?=	streamtuner>=0.99.99nb2
BUILDLINK_PKGSRCDIR.streamtuner?=	../../audio/streamtuner
.endif	# STREAMTUNER_BUILDLINK3_MK

.include "../../www/curl/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
