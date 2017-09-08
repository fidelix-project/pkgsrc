# $NetBSD: buildlink3.mk,v 1.1 2017/09/08 12:58:06 jaapb Exp $

BUILDLINK_TREE+=	ocaml-lwt_react

.if !defined(OCAML_LWT_REACT_BUILDLINK3_MK)
OCAML_LWT_REACT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-lwt_react+=	ocaml-lwt_react>=1.1.0
BUILDLINK_PKGSRCDIR.ocaml-lwt_react?=	../../devel/ocaml-lwt_react

.include "../../devel/ocaml-lwt/buildlink3.mk"
.include "../../devel/ocaml-react/buildlink3.mk"
.endif	# OCAML_LWT_REACT_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-lwt_react
