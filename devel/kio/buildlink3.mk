# $NetBSD: buildlink3.mk,v 1.5 2017/02/06 13:54:39 wiz Exp $

BUILDLINK_TREE+=	kio

.if !defined(KIO_BUILDLINK3_MK)
KIO_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.kio+=	kio>=5.21.0
BUILDLINK_ABI_DEPENDS.kio?=	kio>=5.25.0nb3
BUILDLINK_PKGSRCDIR.kio?=	../../devel/kio

.include "../../devel/zlib/buildlink3.mk"
.include "../../archivers/karchive/buildlink3.mk"
.include "../../devel/kbookmarks/buildlink3.mk"
.include "../../security/kwallet/buildlink3.mk"
.include "../../sysutils/solid/buildlink3.mk"
.include "../../x11/kjobwidgets/buildlink3.mk"
.include "../../x11/qt5-qtbase/buildlink3.mk"
.include "../../x11/qt5-qtscript/buildlink3.mk"
.endif	# KIO_BUILDLINK3_MK

BUILDLINK_TREE+=	-kio
