# $NetBSD: buildlink3.mk,v 1.2 2004/03/05 19:25:36 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
LUA_BUILDLINK3_MK:=	${LUA_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	lua
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nlua}
BUILDLINK_PACKAGES+=	lua

.if !empty(LUA_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.lua+=		lua>=5.0
BUILDLINK_PKGSRCDIR.lua?=	../../lang/lua
.endif	# LUA_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
