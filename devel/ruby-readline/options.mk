# $NetBSD: options.mk,v 1.6 2013/08/21 20:02:50 jperkin Exp $
#

PKG_OPTIONS_VAR=	PKG_OPTIONS.ruby
PKG_SUPPORTED_OPTIONS=	readline ruby-build-ri-db

#
# GNU readline supports multi bytes characters.
#
PKG_SUGGESTED_OPTIONS=	ruby-build-ri-db

.include "../../lang/ruby/rubyversion.mk"

# Since license of Ruby prior to 1.9.3 is incompatible with newer
# readline's GPL3, enable it with 1.9.3 and lator.
#
.if ${RUBY_VER} != 18 && ${RUBY_VER} != 19
PKG_SUGGESTED_OPTIONS+=	readline
.endif

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mreadline)
.  include "../../mk/readline.buildlink3.mk"
.  if ${READLINE_TYPE} == "editline"
CONFIGURE_ARGS+=	--enable-libedit
.  else
CONFIGURE_ARGS+=	--disable-libedit
.  endif
.endif
