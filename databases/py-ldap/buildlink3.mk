# $NetBSD: buildlink3.mk,v 1.7 2006/06/16 10:58:23 rillig Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PY_LDAP_BUILDLINK3_MK:=	${PY_LDAP_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	pyldap
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Npyldap}
BUILDLINK_PACKAGES+=	pyldap

.if !empty(PY_LDAP_BUILDLINK3_MK:M+)
.include "../../lang/python/pyversion.mk"
BUILDLINK_API_DEPENDS.pyldap+=	${PYPKGPREFIX}-ldap>=2.2.0
BUILDLINK_ABI_DEPENDS.pyldap+=	${PYPKGPREFIX}-ldap>=2.2.0
BUILDLINK_PKGSRCDIR.pyldap?=	../../databases/py-ldap
.endif	# PY_LDAP_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
