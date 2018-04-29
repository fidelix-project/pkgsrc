# $NetBSD: buildlink3.mk,v 1.9 2018/04/29 21:31:22 adam Exp $

BUILDLINK_TREE+=	libguardtime

.if !defined(LIBGUARDTIME_BUILDLINK3_MK)
LIBGUARDTIME_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libguardtime+=	libguardtime>=0.3.11
BUILDLINK_ABI_DEPENDS.libguardtime+=	libguardtime>=0.3.13nb7
BUILDLINK_PKGSRCDIR.libguardtime?=	../../security/libguardtime

.include "../../security/openssl/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.endif

BUILDLINK_TREE+=	-libguardtime
