# $NetBSD: buildlink3.mk,v 1.14 2018/01/07 13:04:20 rillig Exp $

BUILDLINK_TREE+=	tcl-otcl

.if !defined(TCL_OTCL_BUILDLINK3_MK)
TCL_OTCL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.tcl-otcl+=	tcl-otcl>=1.8
BUILDLINK_ABI_DEPENDS.tcl-otcl+=	tcl-otcl>=1.14nb4
BUILDLINK_PKGSRCDIR.tcl-otcl?=		../../lang/tcl-otcl

.include "../../lang/tcl/buildlink3.mk"
.include "../../x11/tk/buildlink3.mk"
.endif # TCL_OTCL_BUILDLINK3_MK

BUILDLINK_TREE+=	-tcl-otcl
