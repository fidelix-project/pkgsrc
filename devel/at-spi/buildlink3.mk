# $NetBSD: buildlink3.mk,v 1.35 2013/06/04 22:15:50 tron Exp $

BUILDLINK_TREE+=	at-spi

.if !defined(AT_SPI_BUILDLINK3_MK)
AT_SPI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.at-spi+=	at-spi>=1.6.0
BUILDLINK_ABI_DEPENDS.at-spi+=	at-spi>=1.32.0nb13
BUILDLINK_PKGSRCDIR.at-spi?=	../../devel/at-spi

.include "../../devel/atk/buildlink3.mk"
.include "../../devel/libbonobo/buildlink3.mk"
.include "../../devel/popt/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/libXtst/buildlink3.mk"
.include "../../sysutils/dbus-glib/buildlink3.mk"
.endif # AT_SPI_BUILDLINK3_MK

BUILDLINK_TREE+=	-at-spi
