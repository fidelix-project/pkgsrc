# $NetBSD: buildlink3.mk,v 1.7 2018/01/01 21:18:09 adam Exp $
#

BUILDLINK_TREE+=	librime

.if !defined(LIBRIME_BUILDLINK3_MK)
LIBRIME_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.librime+=	librime>=1.0
BUILDLINK_ABI_DEPENDS.librime?=	librime>=1.0nb7
BUILDLINK_PKGSRCDIR.librime?=	../../inputmethod/librime

.include "../../converters/opencc/buildlink3.mk"
.include "../../databases/kyotocabinet/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/google-glog/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../textproc/yaml-cpp/buildlink3.mk"
.endif	# LIBRIME_BUILDLINK3_MK

BUILDLINK_TREE+=	-librime
