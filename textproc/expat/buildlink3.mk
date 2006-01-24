# $NetBSD: buildlink3.mk,v 1.14 2006/01/24 07:31:52 wiz Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
EXPAT_BUILDLINK3_MK:=	${EXPAT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	expat
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nexpat}
BUILDLINK_PACKAGES+=	expat

.if !empty(EXPAT_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.expat+=	expat>=1.95.7
BUILDLINK_RECOMMENDED.expat+=	expat>=2.0.0
BUILDLINK_PKGSRCDIR.expat?=	../../textproc/expat
.endif	# EXPAT_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
