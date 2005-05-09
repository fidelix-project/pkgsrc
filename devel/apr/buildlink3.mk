# $NetBSD: buildlink3.mk,v 1.16 2005/05/09 05:14:08 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
APR_BUILDLINK3_MK:=	${APR_BUILDLINK3_MK}+

.include "../../mk/bsd.prefs.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	apr
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Napr}
BUILDLINK_PACKAGES+=	apr

.if !empty(APR_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.apr+=	apr>=0.9.5.2.0.51nb1
BUILDLINK_RECOMMENDED.apr+=	apr>=0.9.5.2.0.52nb1
BUILDLINK_PKGSRCDIR.apr?=	../../devel/apr

WRAPPER_REORDER_CMDS+=	reorder:l:aprutil-0:crypt

BUILDLINK_FILES.apr+=	bin/apr-config
BUILDLINK_FILES.apr+=	bin/apu-config
BUILDLINK_FILES.apr+=	lib/*.exp
.endif	# APR_BUILDLINK3_MK

.if !defined(PKG_BUILD_OPTIONS.apr)
PKG_BUILD_OPTIONS.apr!=	cd ${BUILDLINK_PKGSRCDIR.apr} && \
			${MAKE} show-var ${MAKE_FLAGS} VARNAME=PKG_OPTIONS
MAKE_FLAGS+=	PKG_BUILD_OPTIONS.apr=${PKG_BUILD_OPTIONS.apr:Q}
.endif
MAKE_VARS+=	PKG_BUILD_OPTIONS.apr

.if !empty(PKG_BUILD_OPTIONS.apr:Mdb4)
.  include "../../databases/db4/buildlink3.mk"
.endif

.if !empty(PKG_BUILD_OPTIONS.apr:Mldap)
.  include "../../databases/openldap/buildlink3.mk"
.endif

.include "../../textproc/expat/buildlink3.mk"
.include "../../mk/dlopen.buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
