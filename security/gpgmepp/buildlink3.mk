# $NetBSD: buildlink3.mk,v 1.3 2017/02/06 13:54:48 wiz Exp $

BUILDLINK_TREE+=	gpgmepp

.if !defined(GPGMEPP_BUILDLINK3_MK)
GPGMEPP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gpgmepp+=	gpgmepp>=15.12.2
BUILDLINK_ABI_DEPENDS.gpgmepp?=	gpgmepp>=15.12.2nb2
BUILDLINK_PKGSRCDIR.gpgmepp?=	../../security/gpgmepp

.include "../../devel/boost-headers/buildlink3.mk"
.include "../../security/gpgme/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.endif	# GPGMEPP_BUILDLINK3_MK

BUILDLINK_TREE+=	-gpgmepp
