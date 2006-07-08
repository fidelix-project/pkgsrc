# $NetBSD: buildlink3.mk,v 1.6 2006/07/08 22:39:02 jlam Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
VERILOG_CURRENT_BUILDLINK3_MK:=	${VERILOG_CURRENT_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	verilog-current
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nverilog-current}
BUILDLINK_PACKAGES+=	verilog-current
BUILDLINK_ORDER+=	verilog-current

.if !empty(VERILOG_CURRENT_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.verilog-current+=	verilog-current>=20021019
BUILDLINK_ABI_DEPENDS.verilog-current?=	verilog-current>=20060124nb1
BUILDLINK_PKGSRCDIR.verilog-current?=	../../cad/verilog-current
.endif	# VERILOG_CURRENT_BUILDLINK3_MK

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH:S/+$//}
