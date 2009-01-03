# $NetBSD: buildlink3.mk,v 1.2 2009/01/03 19:34:02 gdt Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
PULSEAUDIO_BUILDLINK3_MK:=	${PULSEAUDIO_BUILDLINK3_MK}+

.if ${BUILDLINK_DEPTH} == "+"
BUILDLINK_DEPENDS+=	pulseaudio
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npulseaudio}
BUILDLINK_PACKAGES+=	pulseaudio
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}pulseaudio

.if ${PULSEAUDIO_BUILDLINK3_MK} == "+"
BUILDLINK_API_DEPENDS.pulseaudio+=	pulseaudio>=0.9.13
BUILDLINK_PKGSRCDIR.pulseaudio?=	../../audio/pulseaudio
.endif	# PULSEAUDIO_BUILDLINK3_MK

.include "../../devel/glib2/buildlink3.mk"

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
