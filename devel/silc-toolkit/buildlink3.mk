# $NetBSD: buildlink3.mk,v 1.3 2006/04/06 06:21:56 reed Exp $
#

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
SILC_TOOLKIT_BUILDLINK3_MK:=	${SILC_TOOLKIT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	silc-toolkit
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nsilc-toolkit}
BUILDLINK_PACKAGES+=	silc-toolkit

.if !empty(SILC_TOOLKIT_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.silc-toolkit+=	silc-toolkit>=0.9.12
BUILDLINK_ABI_DEPENDS.silc-toolkit+=	silc-toolkit>=0.9.12nb1
BUILDLINK_PKGSRCDIR.silc-toolkit?=	../../devel/silc-toolkit
.endif	# SILC_TOOLKIT_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
