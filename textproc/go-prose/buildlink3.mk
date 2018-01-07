# $NetBSD: buildlink3.mk,v 1.3 2018/01/07 13:04:33 rillig Exp $

BUILDLINK_TREE+=	go-prose

.if !defined(GO_PROSE_BUILDLINK3_MK)
GO_PROSE_BUILDLINK3_MK:=

BUILDLINK_CONTENTS_FILTER.go-prose=	${EGREP} gopkg/
BUILDLINK_DEPMETHOD.go-prose?=		build

BUILDLINK_API_DEPENDS.go-prose+=	go-prose>=0.0
BUILDLINK_PKGSRCDIR.go-prose?=		../../textproc/go-prose

.endif  # GO_PROSE_BUILDLINK3_MK

BUILDLINK_TREE+=	-go-prose
