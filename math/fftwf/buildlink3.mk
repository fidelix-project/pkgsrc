# $NetBSD: buildlink3.mk,v 1.5 2006/07/08 22:39:27 jlam Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
FFTWF_BUILDLINK3_MK:=	${FFTWF_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	fftwf
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nfftwf}
BUILDLINK_PACKAGES+=	fftwf
BUILDLINK_ORDER+=	fftwf

.if !empty(FFTWF_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.fftwf+=	fftwf>=3.0
BUILDLINK_ABI_DEPENDS.fftwf+=	fftwf>=3.0.1nb1
BUILDLINK_PKGSRCDIR.fftwf?=	../../math/fftwf
.endif	# FFTWF_BUILDLINK3_MK

.include "../../math/fftw/buildlink3.mk"

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
