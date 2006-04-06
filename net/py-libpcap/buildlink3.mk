# $NetBSD: buildlink3.mk,v 1.3 2006/04/06 06:22:34 reed Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PYLIBPCAP_BUILDLINK3_MK:=	${PYLIBPCAP_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pylibpcap
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npylibpcap}
BUILDLINK_PACKAGES+=	pylibpcap

.if !empty(PYLIBPCAP_BUILDLINK3_MK:M+)

.include "../../lang/python/pyversion.mk"

BUILDLINK_API_DEPENDS.pylibpcap+=	${PYPKGPREFIX}-libpcap>=0.5.0
BUILDLINK_ABI_DEPENDS.pylibpcap?=	${PYPKGPREFIX}-libpcap>=0.5nb1
BUILDLINK_PKGSRCDIR.pylibpcap?=	../../net/py-libpcap

.endif	# PYLIBPCAP_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
