# $NetBSD: buildlink3.mk,v 1.17 2012/06/14 07:43:22 sbd Exp $

BUILDLINK_TREE+=	php

.if !defined(PHP_BUILDLINK3_MK)
PHP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.php+=		php>=5.1.2<5.3
BUILDLINK_ABI_DEPENDS.php+=	php>=5.2.17nb6
BUILDLINK_PKGSRCDIR.php?=	../../lang/php5

.include "../../textproc/libxml2/buildlink3.mk"
.endif # PHP_BUILDLINK3_MK

BUILDLINK_TREE+=	-php
