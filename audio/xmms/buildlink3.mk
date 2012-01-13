# $NetBSD: buildlink3.mk,v 1.13 2012/01/13 10:54:49 obache Exp $

BUILDLINK_TREE+=	xmms

.if !defined(XMMS_BUILDLINK3_MK)
XMMS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.xmms+=	xmms>=1.2.7nb10
BUILDLINK_ABI_DEPENDS.xmms?=	xmms>=1.2.11nb3
BUILDLINK_PKGSRCDIR.xmms?=	../../audio/xmms

PTHREAD_OPTS+=	require

.include "../../audio/libmikmod/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../x11/gtk/buildlink3.mk"

.include "../../mk/pthread.buildlink3.mk"
.endif # XMMS_BUILDLINK3_MK

BUILDLINK_TREE+=	-xmms
