# $NetBSD: buildlink3.mk,v 1.2 2018/01/07 13:04:01 rillig Exp $

BUILDLINK_TREE+=	go-check

.if !defined(GO_CHECK_BUILDLINK3_MK)
GO_CHECK_BUILDLINK3_MK:=

BUILDLINK_CONTENTS_FILTER.go-check=	${EGREP} gopkg/
BUILDLINK_DEPMETHOD.go-check?=		build

BUILDLINK_API_DEPENDS.go-check+=	go-check>=1
BUILDLINK_PKGSRCDIR.go-check?=		../../devel/go-check
.endif	# GO_CHECK_BUILDLINK3_MK

BUILDLINK_TREE+=	-go-check
