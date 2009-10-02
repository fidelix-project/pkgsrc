# $NetBSD: buildlink3.mk,v 1.1.1.1 2009/10/02 10:05:54 hasso Exp $

BUILDLINK_TREE+=	libpreludedb-sqlite3

.if !defined(LIBPRELUDEDB_SQLITE3_BUILDLINK3_MK)
LIBPRELUDEDB_SQLITE3_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libpreludedb-sqlite3+=	libpreludedb-sqlite3>=0.9.15.3
BUILDLINK_PKGSRCDIR.libpreludedb-sqlite3?=	../../security/libpreludedb-sqlite3

.endif	# LIBPRELUDEDB_SQLITE3_BUILDLINK3_MK

BUILDLINK_TREE+=	-libpreludedb-sqlite3
