# $NetBSD: buildlink3.mk,v 1.2 2004/10/03 00:13:01 tv Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
AVIFILE_BUILDLINK3_MK:=	${AVIFILE_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	avifile
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Navifile}
BUILDLINK_PACKAGES+=	avifile

.if !empty(AVIFILE_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.avifile+=	avifile>=0.53.5nb2
BUILDLINK_RECOMMENDED.avifile+=	avifile>=0.53.5nb3
BUILDLINK_PKGSRCDIR.avifile?=	../../multimedia/avifile
.endif	# AVIFILE_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
