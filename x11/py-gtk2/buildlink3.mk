# $NetBSD: buildlink3.mk,v 1.56 2017/02/06 13:54:57 wiz Exp $

BUILDLINK_TREE+=	pygtk2

.if !defined(PYGTK2_BUILDLINK3_MK)
PYGTK2_BUILDLINK3_MK:=

.include "../../lang/python/pyversion.mk"

BUILDLINK_API_DEPENDS.pygtk2+=	${PYPKGPREFIX}-gtk2>=2.8.4
BUILDLINK_ABI_DEPENDS.pygtk2+=	${PYPKGPREFIX}-gtk2>=2.24.0nb21
BUILDLINK_PKGSRCDIR.pygtk2?=	../../x11/py-gtk2

.include "../../devel/py-gobject/buildlink3.mk"
.include "../../devel/libglade/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.endif # PYGTK2_BUILDLINK3_MK

BUILDLINK_TREE+=	-pygtk2
