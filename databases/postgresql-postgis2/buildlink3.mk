# $NetBSD: buildlink3.mk,v 1.8 2018/05/21 08:12:23 adam Exp $

BUILDLINK_TREE+=	postgresql-postgis

.if !defined(POSTGRESQL_POSTGIS_BUILDLINK3_MK)
POSTGRESQL_POSTGIS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.postgresql-postgis+=	postgresql${PGSQL_VERSION}-postgis>=1.4
BUILDLINK_ABI_DEPENDS.postgresql-postgis?=	postgresql${PGSQL_VERSION}-postgis>=2.2.2nb3
BUILDLINK_PKGSRCDIR.postgresql-postgis?=	../../databases/postgresql-postgis2

PGSQL_VERSIONS_ACCEPTED=	94 93

.include "../../geography/geos/buildlink3.mk"
.include "../../geography/proj/buildlink3.mk"
.include "../../mk/pgsql.buildlink3.mk"
.endif	# POSTGRESQL_POSTGIS_BUILDLINK3_MK

BUILDLINK_TREE+=	-postgresql-postgis
