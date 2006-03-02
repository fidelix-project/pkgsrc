# $NetBSD: buildlink3.mk,v 1.4 2006/03/02 21:37:31 wiz Exp $

BUILDLINK_DEPTH:=		${BUILDLINK_DEPTH}+
SUN_JDK14_BUILDLINK3_MK:=	${SUN_JDK14_BUILDLINK3_MK}+

.if !empty(BUILDLINK_DEPTH:M+)
BUILDLINK_DEPENDS+=	sun-jdk14
.endif

BUILDLINK_PACKAGES:=	${BUILDLINK_PACKAGES:Nsun-jdk14}
BUILDLINK_PACKAGES+=	sun-jdk14

.if !empty(SUN_JDK14_BUILDLINK3_MK:M+)

BUILDLINK_DEPENDS.sun-jdk14+=	sun-jdk14-[0-9]*
BUILDLINK_RECOMMENDED.sun-jdk14?=	sun-jdk14>=2.9nb1
BUILDLINK_PKGSRCDIR.sun-jdk14?=	../../lang/sun-jdk14
BUILDLINK_DEPMETHOD.sun-jdk14?= build

BUILDLINK_PASSTHRU_DIRS+=	${BUILDLINK_JAVA_PREFIX.sun-jre14}

BUILDLINK_CPPFLAGS.sun-jdk14+=						\
	-I${BUILDLINK_JAVA_PREFIX.sun-jre14}/include			\
	-I${BUILDLINK_JAVA_PREFIX.sun-jre14}/include/linux

.include "../../lang/sun-jre14/buildlink3.mk"

.endif	# SUN_JDK14_BUILDLINK3_MK

BUILDLINK_DEPTH:=     ${BUILDLINK_DEPTH:S/+$//}
