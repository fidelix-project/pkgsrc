# $NetBSD: buildlink3.mk,v 1.12 2008/05/29 20:27:47 tnn Exp $

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH}+
MPICH2_BUILDLINK3_MK:=	${MPICH2_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	mpich2
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nmpich2}
BUILDLINK_PACKAGES+=	mpich2
BUILDLINK_ORDER:=	${BUILDLINK_ORDER} ${BUILDLINK_DEPTH}mpich2

.if !empty(MPICH2_BUILDLINK3_MK:M+)
BUILDLINK_API_DEPENDS.mpich2+=	mpich2>=1.0.7
BUILDLINK_PKGSRCDIR.mpich2?=	../../parallel/mpi-ch
BUILDLINK_DEPMETHOD.mpich2?=	build
.endif	# MPICH2_BUILDLINK3_MK

BUILDLINK_DEPTH:=	${BUILDLINK_DEPTH:S/+$//}
