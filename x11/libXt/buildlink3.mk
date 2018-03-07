# $NetBSD: buildlink3.mk,v 1.8 2018/03/07 11:57:37 wiz Exp $

.include "../../mk/bsd.fast.prefs.mk"

.if ${X11_TYPE} != "modular" && \
    !exists(${X11BASE}/lib/pkgconfig/xt.pc) && \
    !exists(${X11BASE}/lib${LIBABISUFFIX}/pkgconfig/xt.pc)
.include "../../mk/x11.buildlink3.mk"
.else

BUILDLINK_TREE+=	libXt

.  if !defined(LIBXT_BUILDLINK3_MK)
LIBXT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libXt+=	libXt>=1.0.0
BUILDLINK_PKGSRCDIR.libXt?=	../../x11/libXt

.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/xorgproto/buildlink3.mk"
.  endif # LIBXT_BUILDLINK3_MK

BUILDLINK_TREE+=	-libXt

.endif
