# $NetBSD: buildlink3.mk,v 1.3 2018/01/10 16:53:09 jaapb Exp $

BUILDLINK_TREE+=	ocaml-lwt_ssl

.if !defined(OCAML_LWT_SSL_BUILDLINK3_MK)
OCAML_LWT_SSL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ocaml-lwt_ssl+=	ocaml-lwt_ssl>=1.1.0
BUILDLINK_ABI_DEPENDS.ocaml-lwt_ssl?=	ocaml-lwt_ssl>=1.1.0nb1
BUILDLINK_PKGSRCDIR.ocaml-lwt_ssl?=	../../devel/ocaml-lwt_ssl

.include "../../devel/ocaml-lwt/buildlink3.mk"
.include "../../security/ocaml-ssl/buildlink3.mk"
.endif	# OCAML_LWT_SSL_BUILDLINK3_MK

BUILDLINK_TREE+=	-ocaml-lwt_ssl
