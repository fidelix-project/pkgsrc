# $NetBSD: buildlink3.mk,v 1.5 2018/01/10 16:09:33 jaapb Exp $

BUILDLINK_TREE+=	ocaml-sexplib

.if !defined(OCAML_SEXPLIB_BUILDLINK3_MK)
OCAML_SEXPLIB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-sexplib+=	ocaml-sexplib>=0.9.0
BUILDLINK_ABI_DEPENDS.ocaml-sexplib+=	ocaml-sexplib>=0.10.0
BUILDLINK_PKGSRCDIR.ocaml-sexplib?=	../../devel/ocaml-sexplib

.endif	# OCAML_SEXPLIB_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-sexplib
