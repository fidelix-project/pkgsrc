# $NetBSD: buildlink3.mk,v 1.7 2006/04/07 05:21:01 minskim Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
TETEX_BIN_BUILDLINK3_MK:=	${TETEX_BIN_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	teTeX-bin
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:NteTeX-bin}
BUILDLINK_PACKAGES+=	teTeX-bin

.if !empty(TETEX_BIN_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.teTeX-bin+=	teTeX-bin>=3.0nb2
BUILDLINK_ABI_DEPENDS.teTeX-bin?=	teTeX-bin>=3.0nb7
BUILDLINK_PKGSRCDIR.teTeX-bin?=	../../print/teTeX3-bin
.endif	# TETEX_BIN_BUILDLINK3_MK

TEX=etex
PDFTEX=pdfetex
#PKG_TEXMFPREFIX=	${PREFIX}/share/texmf-dist
PKG_TEXMFPREFIX=	${PREFIX}/share/texmf
PKG_LOCALTEXMFPREFIX=	${PREFIX}/share/texmf-local
PLIST_SUBST+=	PKG_TEXMFPREFIX=${PKG_TEXMFPREFIX:C|^${PREFIX}/||}
PLIST_SUBST+=	PKG_LOCALTEXMFPREFIX=${PKG_LOCALTEXMFPREFIX:C|^${PREFIX}/||}

PRINT_PLIST_AWK+=	/^@dirrm ${PKG_LOCALTEXMFPREFIX:S|${PREFIX}/||:S|/|\\/|g}(\/bibtex(\/bib|\/bst)?|\/tex(\/latex)?)?$$/ \
			{ next; }
PRINT_PLIST_AWK+=	/^(@dirrm )?${PKG_LOCALTEXMFPREFIX:S|${PREFIX}/||:S|/|\\/|g}/ \
			{ gsub(/${PKG_LOCALTEXMFPREFIX:S|${PREFIX}/||:S|/|\\/|g}/, "$${PKG_LOCALTEXMFPREFIX}"); \
			print; next; }

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
