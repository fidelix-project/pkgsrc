# $NetBSD: buildlink3.mk,v 1.3 2004/11/01 19:52:58 jdolecek Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
PHP_BUILDLINK3_MK:=	${PHP_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	php
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nphp}
BUILDLINK_PACKAGES+=	php

.if !empty(PHP_BUILDLINK3_MK:M+)
BUILDLINK_DEPENDS.php+=	php-5.0.*
BUILDLINK_PKGSRCDIR.php?=	../../lang/php5

# Use full dependency for extension and pear modules
BUILDLINK_DEPMETHOD.php?=	full
.endif	# PHP_BUILDLINK3_MK

.include "../../textproc/libxml2/buildlink3.mk"

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
