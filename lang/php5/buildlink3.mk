# $NetBSD: buildlink3.mk,v 1.11 2006/04/06 06:22:13 reed Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PHP_BUILDLINK3_MK:=	${PHP_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	php
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nphp}
BUILDLINK_PACKAGES+=	php

.if !empty(PHP_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.php+=		php>=5.1.2
BUILDLINK_ABI_DEPENDS.php+=	php>=5.1.2
BUILDLINK_PKGSRCDIR.php?=	../../lang/php5
.endif	# PHP_BUILDLINK3_MK

.include "../../textproc/libxml2/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
