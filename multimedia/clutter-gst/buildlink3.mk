# $NetBSD: buildlink3.mk,v 1.8 2010/11/15 22:58:03 abs Exp $
#

BUILDLINK_TREE+=	clutter-gst

.if !defined(CLUTTER_GST_BUILDLINK3_MK)
CLUTTER_GST_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.clutter-gst+=	clutter-gst>=1.0.0
BUILDLINK_ABI_DEPENDS.clutter-gst?=	clutter-gst>=1.2.0nb1
BUILDLINK_PKGSRCDIR.clutter-gst?=	../../multimedia/clutter-gst

.include "../../graphics/clutter/buildlink3.mk"
.include "../../multimedia/gstreamer0.10/buildlink3.mk"
.include "../../multimedia/gst-plugins0.10-base/buildlink3.mk"
.endif # CLUTTER_GST_BUILDLINK3_MK

BUILDLINK_TREE+=	-clutter-gst
