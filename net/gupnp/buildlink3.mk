# $NetBSD: buildlink3.mk,v 1.11 2012/03/03 00:12:01 wiz Exp $

BUILDLINK_TREE+=	gupnp

.if !defined(GUPNP_BUILDLINK3_MK)
GUPNP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gupnp+=	gupnp>=0.13.2
BUILDLINK_ABI_DEPENDS.gupnp?=	gupnp>=0.13.3nb6
BUILDLINK_PKGSRCDIR.gupnp?=	../../net/gupnp

.include "../../mk/bsd.prefs.mk"
.if !empty(OPSYS:M*BSD) || ${OPSYS} == "DragonFly"
pre-configure:
	cp ${BUILDLINK_PKGSRCDIR.gupnp}/files/uuid.pc ${BUILDLINK_DIR}/lib/pkgconfig/
.else
.include "../../devel/libuuid/buildlink3.mk"
.endif

.include "../../devel/glib2/buildlink3.mk"
.include "../../net/libsoup24/buildlink3.mk"
.include "../../net/gssdp/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.endif	# GUPNP_BUILDLINK3_MK

BUILDLINK_TREE+=	-gupnp
