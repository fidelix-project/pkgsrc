# $NetBSD: buildlink3.mk,v 1.16 2004/07/10 03:01:38 grant Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
DB_BUILDLINK3_MK:=	${DB_BUILDLINK3_MK}+

.include "../../mk/bsd.prefs.mk"

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	db2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Ndb2}
BUILDLINK_PACKAGES+=	db2

.if !empty(DB_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.db2+=		db>=2.7.3
BUILDLINK_PKGSRCDIR.db2?=	../../databases/db
.  if defined(USE_DB185)
BUILDLINK_INCDIRS.db2?=		include/db2
BUILDLINK_LIBDIRS.db2?=		lib
BUILDLINK_TRANSFORM+=		l:db:db2
BUILDLINK_CPPFLAGS.db2=		-I${BUILDLINK_PREFIX.db2}/${BUILDLINK_INCDIRS.db2}
.  endif
BUILDLINK_LDFLAGS.db2=		-L${BUILDLINK_PREFIX.db2}/lib -Wl,${RPATH_FLAG}${BUILDLINK_PREFIX.db2}/lib
BUILDLINK_LIBS.db2=		-ldb2
.endif	# DB_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
