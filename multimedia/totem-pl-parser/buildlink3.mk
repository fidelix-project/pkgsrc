# $NetBSD: buildlink3.mk,v 1.19 2012/04/27 12:31:56 obache Exp $

BUILDLINK_TREE+=	totem-pl-parser

.if !defined(TOTEM_PL_PARSER_BUILDLINK3_MK)
TOTEM_PL_PARSER_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.totem-pl-parser+=	totem-pl-parser>=2.22.1
BUILDLINK_ABI_DEPENDS.totem-pl-parser?=	totem-pl-parser>=2.32.6nb4
BUILDLINK_PKGSRCDIR.totem-pl-parser?=	../../multimedia/totem-pl-parser

.include "../../devel/glib2/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mail/gmime24/buildlink3.mk"
.include "../../net/libsoup24/buildlink3.mk"
.endif # TOTEM_PL_PARSER_BUILDLINK3_MK

BUILDLINK_TREE+=	-totem-pl-parser
