# $NetBSD: buildlink3.mk,v 1.5 2018/01/07 13:04:26 rillig Exp $

BUILDLINK_TREE+=	isc-dhcp

.if !defined(ISC_DHCP_BUILDLINK3_MK)
ISC_DHCP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.isc-dhcp+=	isc-dhcp>=4.3.0
BUILDLINK_PKGSRCDIR.isc-dhcp?=		../../net/isc-dhcp4
.endif # ISC_DHCP_BUILDLINK3_MK

BUILDLINK_TREE+=	-isc-dhcp
