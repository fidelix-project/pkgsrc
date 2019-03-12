# $NetBSD: buildlink3.mk,v 1.1 2019/03/12 18:22:34 jaapb Exp $

BUILDLINK_TREE+=	ocaml-ppx_let

.if !defined(OCAML_PPX_LET_BUILDLINK3_MK)
OCAML_PPX_LET_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-ppx_let+=	ocaml-ppx_let>=0.12.0
BUILDLINK_PKGSRCDIR.ocaml-ppx_let?=	../../devel/ocaml-ppx_let

.endif	# OCAML_PPX_LET_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-ppx_let
