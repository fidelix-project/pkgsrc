# $NetBSD: buildlink3.mk,v 1.2 2004/10/03 00:13:34 tv Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
UCL_BUILDLINK3_MK:=	${UCL_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	ucl
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nucl}
BUILDLINK_PACKAGES+=	ucl

.if !empty(UCL_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.ucl+=	ucl>=1.02
BUILDLINK_RECOMMENDED.ucl+=	ucl>=1.02nb2
BUILDLINK_PKGSRCDIR.ucl?=	../../devel/ucl
.endif	# UCL_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
