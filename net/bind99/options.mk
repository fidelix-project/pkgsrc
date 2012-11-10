# $NetBSD: options.mk,v 1.4 2012/11/10 23:45:39 pettai Exp $

PKG_OPTIONS_VAR=        PKG_OPTIONS.bind99
PKG_SUPPORTED_OPTIONS=  bind-dig-sigchase bind-xml-statistics-server
PKG_SUPPORTED_OPTIONS+=	inet6 threads readline mysql pgsql ldap dlz-filesystem
PKG_SUPPORTED_OPTIONS+=	rrl
PKG_SUGGESTED_OPTIONS+=	readline

PTHREAD_OPTS+=		native
.include "../../mk/pthread.buildlink3.mk"

.if defined(PTHREAD_TYPE) && (${PTHREAD_TYPE} == "none") || \
	!empty(MACHINE_PLATFORM:MNetBSD-*-vax) || \
	!empty(MACHINE_PLATFORM:MNetBSD-*-sparc) || \
	!empty(MACHINE_PLATFORM:MNetBSD-*-sparc64) || \
	!empty(MACHINE_PLATFORM:MNetBSD-*-m68k)
# don't touch PKG_SUGGESTED_OPTIONS
.else
PKG_SUGGESTED_OPTIONS+=	threads
.endif

.if empty(MISSING_FEATURES:Minet6)
PKG_SUGGESTED_OPTIONS+=	inet6
.endif

.include "../../mk/bsd.options.mk"

###
### The mysql pgsql ldap dlz-filesystem options are all for BIND
### DLZ (Dynamically Loadable Zones) functionality
###
### NOTE: bdb is excluded on purpose as pkgsrc does not contain
###       a bdb v4.1 or 4.2 package which is what BIND needs.
###       The majority of these are compile tested only
###

.if !empty(PKG_OPTIONS:Mmysql)
.include "../../mk/mysql.buildlink3.mk"
CONFIGURE_ARGS+=	--with-dlz-mysql=${BUILDLINK_PREFIX.mysql-client}
.endif

.if !empty(PKG_OPTIONS:Mpgsql)
.include "../../mk/pgsql.buildlink3.mk"
CONFIGURE_ARGS+=	--with-dlz-postgres=${BUILDLINK_PREFIX.${PGSQL_TYPE}}
CONFIGURE_ENV+=		ac_cv_path_PG_CONFIG=${PREFIX}/bin/pg_config
.endif

.if !empty(PKG_OPTIONS:Mldap)
.include "../../databases/openldap-client/buildlink3.mk"
CONFIGURE_ARGS+=	--with-dlz-ldap=${BUILDLINK_PREFIX.openldap-client}
.endif

.if !empty(PKG_OPTIONS:Mdlz-filesystem)
CONFIGURE_ARGS+=	--with-dlz-filesystem
.endif

.if !empty(PKG_OPTIONS:Mrrl)
PATCHFILES=rl-9.9.2.patch
PATCH_SITES=http://ss.vix.com/~vixie/
.endif

###
### The statistics server in bind99 and later needs libxml2
###
.if !empty(PKG_OPTIONS:Mbind-xml-statistics-server)
.include "../../textproc/libxml2/buildlink3.mk"
CONFIGURE_ARGS+=	--with-libxml2
.else
CONFIGURE_ARGS+=	--without-libxml2
.endif

###
### IPv6 support
###
.if !empty(PKG_OPTIONS:Minet6)
CONFIGURE_ARGS+=	--enable-ipv6
.else
CONFIGURE_ARGS+=	--disable-ipv6
.endif

###
### pthreads support (also see magic above)
###
.if !empty(PKG_OPTIONS:Mthreads)
PTHREAD_AUTO_VARS=	yes
CONFIGURE_ARGS+=	--enable-threads
.else
CONFIGURE_ARGS+=	--disable-threads
.endif

###
### readline support in dig(1) and nsupdate(1).
###
.if !empty(PKG_OPTIONS:Mreadline)
.include "../../devel/readline/buildlink3.mk"
CONFIGURE_ARGS+=	--with-readline
.else
CONFIGURE_ARGS+=	--without-readline
.endif

###
### dig(1) option +sigchase for DNSSEC signature chasing
###
.if !empty(PKG_OPTIONS:Mbind-dig-sigchase)
# If anything else needs to add entries to STD_CDEFINES, this will need
# to be changed so that the two can cooperate.
CONFIGURE_ENV+=		STD_CDEFINES=-DDIG_SIGCHASE=1
.endif
