# $NetBSD: buildlink3.mk,v 1.2 2016/12/04 05:17:11 ryoon Exp $

BUILDLINK_TREE+=	kwallet

.if !defined(KWALLET_BUILDLINK3_MK)
KWALLET_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.kwallet+=	kwallet>=5.19.0
BUILDLINK_ABI_DEPENDS.kwallet?=	kwallet>=5.25.0nb1
BUILDLINK_PKGSRCDIR.kwallet?=	../../security/kwallet

.include "../../devel/knotifications/buildlink3.mk"
.include "../../devel/kservice/buildlink3.mk"
.include "../../graphics/kiconthemes/buildlink3.mk"
.include "../../security/gpgmepp/buildlink3.mk"
.include "../../security/libgcrypt/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.endif	# KWALLET_BUILDLINK3_MK

BUILDLINK_TREE+=	-kwallet
