# $NetBSD: options.mk,v 1.15 2016/01/13 22:26:53 wiz Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.pidgin
PKG_SUPPORTED_OPTIONS+=		dbus debug gtkspell farstream x11
PKG_SUGGESTED_OPTIONS+=		dbus gtkspell farstream x11

.include "../../mk/bsd.options.mk"

PLIST_VARS+=		dbus vv x11

.if !empty(PKG_OPTIONS:Mdbus)
CONFIGURE_ARGS+=	--enable-dbus
PLIST.dbus=		yes
.  include "../../sysutils/dbus/buildlink3.mk"
.  include "../../sysutils/dbus-glib/buildlink3.mk"
.endif

# voice/video support requires both farstream
.if !empty(PKG_OPTIONS:Mfarstream)
CONFIGURE_ARGS+=	--enable-vv
PLIST.vv=		yes
.else
CONFIGURE_ARGS+=	--disable-vv
.endif

.if !empty(PKG_OPTIONS:Mfarstream)
CONFIGURE_ARGS+=	--enable-farstream
.  include "../../chat/farstream/buildlink3.mk"
.endif

.if !empty(PKG_OPTIONS:Mgtkspell)
CONFIGURE_ARGS+=	--enable-gtkspell
.  include "../../textproc/gtkspell/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-gtkspell
.endif

.if !empty(PKG_OPTIONS:Mdebug)
CONFIGURE_ARGS+=	--enable-debug
.endif

.if !empty(PKG_OPTIONS:Mx11)
PLIST.x11=		yes
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/libXScrnSaver/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--without-x
.endif
