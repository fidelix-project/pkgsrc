# $NetBSD: buildlink3.mk,v 1.16 2020/03/10 22:09:02 wiz Exp $

BUILDLINK_TREE+=	kcodecs

.if !defined(KCODECS_BUILDLINK3_MK)
KCODECS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.kcodecs+=	kcodecs>=5.18.0
BUILDLINK_ABI_DEPENDS.kcodecs?=	kcodecs>=5.66.0nb2
BUILDLINK_PKGSRCDIR.kcodecs?=	../../textproc/kcodecs

.include "../../x11/qt5-qtbase/buildlink3.mk"
.endif	# KCODECS_BUILDLINK3_MK

BUILDLINK_TREE+=	-kcodecs
