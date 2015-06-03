# $NetBSD: buildlink3.mk,v 1.1 2015/06/03 11:00:15 fhajny Exp $

BUILDLINK_TREE+=	spdylay

.if !defined(SPDYLAY_BUILDLINK3_MK)
SPDYLAY_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.spdylay+=	spdylay>=1.3.2
BUILDLINK_ABI_DEPENDS.spdylay+=	spdylay>=1.3.2
BUILDLINK_PKGSRCDIR.spdylay?=	../../www/spdylay

.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.endif # SPDYLAY_BUILDLINK3_MK

BUILDLINK_TREE+=	-spdylay
