# $NetBSD: buildlink3.mk,v 1.2 2004/03/06 11:58:43 kristerw Exp $

BUILDLINK_DEPTH:=			${BUILDLINK_DEPTH}+
LIBMODPLUG_BUILDLINK3_MK:=		${LIBMODPLUG_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=			libmodplug
.endif

.if !empty(LIBMODPLUG_BUILDLINK3_MK:M+)
BUILDLINK_PACKAGES+=			libmodplug
BUILDLINK_DEPENDS.libmodplug+=		libmodplug>=0.7
BUILDLINK_PKGSRCDIR.libmodplug?=	../../audio/libmodplug

.endif # LIBMODPLUG_BUILDLINK3_MK

BUILDLINK_DEPTH:=    			 ${BUILDLINK_DEPTH:S/+$//}
