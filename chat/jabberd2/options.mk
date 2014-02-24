# $NetBSD: options.mk,v 1.26 2014/02/24 19:30:53 schnoebe Exp $

PKG_OPTIONS_VAR=		PKG_OPTIONS.jabberd2
PKG_OPTIONS_REQUIRED_GROUPS=	auth storage mio
# Authentication backend
PKG_OPTIONS_GROUP.auth=		auth-mysql auth-pgsql auth-sqlite
PKG_OPTIONS_GROUP.auth+=	auth-db auth-ldap auth-pam
# Storage backend
PKG_OPTIONS_GROUP.storage=	storage-mysql storage-pgsql
PKG_OPTIONS_GROUP.storage+=	storage-sqlite storage-db
# mio implementations
PKG_OPTIONS_GROUP.mio=		mio-kqueue mio-select mio-poll mio-epoll
# debugging
PKG_SUPPORTED_OPTIONS+=		debug

PKG_SUGGESTED_OPTIONS=		auth-sqlite storage-sqlite
PKG_SUGGESTED_OPTIONS+=		mio-select mio-poll

.include "../../mk/bsd.options.mk"

PLIST_VARS+=	db ldap mysql pam pgsql sqlite

.if !empty(PKG_OPTIONS:Mauth-db) || !empty(PKG_OPTIONS:Mstorage-db)
BDB_ACCEPTED=		db4 db5
CONFIGURE_ARGS+=	--enable-db
PLIST.db=		yes
BUILDLINK_TRANSFORM+=	l:db:${BDB_TYPE}
.  include "../../mk/bdb.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-db
.endif

.if !empty(PKG_OPTIONS:Mauth-mysql) || !empty(PKG_OPTIONS:Mstorage-mysql)
PLIST.mysql=		yes
CONFIGURE_ARGS+=	--enable-mysql
CPPFLAGS+=		-I${BUILDLINK_PREFIX.mysql-client}/include/mysql
.  include "../../mk/mysql.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-mysql
.endif

.if !empty(PKG_OPTIONS:Mauth-pgsql) || !empty(PKG_OPTIONS:Mstorage-pgsql)
PLIST.pgsql=		yes
CONFIGURE_ARGS+=	--enable-pgsql
.  include "../../mk/pgsql.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-pgsql
.endif

.if !empty(PKG_OPTIONS:Mauth-sqlite) || !empty(PKG_OPTIONS:Mstorage-sqlite)
PLIST.sqlite=		yes
CONFIGURE_ARGS+=	--enable-sqlite
.  include "../../databases/sqlite3/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-sqlite
.endif

.if !empty(PKG_OPTIONS:Mauth-ldap)
PLIST.ldap=		yes
CONFIGURE_ARGS+=	--enable-ldap
.  include "../../databases/openldap-client/buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-ldap
.endif

.if !empty(PKG_OPTIONS:Mauth-pam)
PLIST.pam=		yes
CONFIGURE_ARGS+=	--enable-pam
.  include "../../mk/pam.buildlink3.mk"
.else
CONFIGURE_ARGS+=	--disable-pam
.endif

.if !empty(PKG_OPTIONS:Mdebug)
CONFIGURE_ARGS+=	--enable-debug
CONFIGURE_ARGS+=	--enable-developer
# CONFIGURE_ARGS+=	--enable-nad-debug
# CONFIGURE_ARGS+=	--enable-pool-debug
# CONFIGURE_ARGS+=	--enable-mio-debug
.endif

.if !empty(PKG_OPTIONS:Mmio-kqueue)
CONFIGURE_ARGS+=	--enable-mio=kqueue
.endif

.if !empty(PKG_OPTIONS:Mmio-epoll)
CONFIGURE_ARGS+=	--enable-mio=epoll
.endif

.if !empty(PKG_OPTIONS:Mmio-poll)
CONFIGURE_ARGS+=	--enable-mio=poll
.endif

.if !empty(PKG_OPTIONS:Mmio-select)
CONFIGURE_ARGS+=	--enable-mio=select
.endif
