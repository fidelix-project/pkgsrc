# $NetBSD: apache.mk,v 1.14 2006/10/14 01:09:45 rillig Exp $
#
# This file is meant to be included by packages that require an apache
# web server.
#
# User-settable variables:
#
# PKG_APACHE_DEFAULT
#	The default apache server to use and install. If there already
#	is an apache installed, this will have no effect.
#
#	Possible values: apache13 apache2
#
# Package-settable variables:
#
# PKG_APACHE_ACCEPTED
#	The list of apache packages that can be used as a dependency for
#	the package.
#
#	Possible values: (see PKG_APACHE_DEFAULT)
#
# USE_APR
#	If apache2 is chosen by this file and this variable is set to
#	"yes", a full dependency to the Apache Portable Runtime library
#	will be added.
#
# Variables defined by this file:
#
# PKG_APACHE
#	The Apache version that is actually used.
#
#	Possible values: (see PKG_APACHE_DEFAULT)
#
# APACHE_PKG_PREFIX
#	The package name prefix for apache modules.
#
#	Possible values: ap13 ap2
#

.if !defined(APACHE_MK)
APACHE_MK=			# defined

.include "../../mk/bsd.prefs.mk"

# User-settable variables
PKG_APACHE_DEFAULT?=		apache2
BUILD_DEFS+=			PKG_APACHE_DEFAULT

# Package-settable variables
PKG_APACHE_ACCEPTED?=		${_PKG_APACHES}
USE_APR?=			no

# The available apache packages:
_PKG_APACHES=			apache13 apache2

_APACHE_PKGBASE.apache13=	apache-1\*
_APACHE_PKG_PREFIX.apache13=	ap13
_APACHE_PKGSRCDIR.apache13=	../../www/apache

_APACHE_PKGBASE.apache2=	apache-2\*
_APACHE_PKG_PREFIX.apache2=	ap2
_APACHE_PKGSRCDIR.apache2=	../../www/apache2

#
# Sanity checks.
#

.if empty(_PKG_APACHES:M${PKG_APACHE_DEFAULT})
PKG_FAIL_REASON+=		"[apache.mk] Invalid apache package \""${PKG_APACHE_DEFAULT:Q}"\" in PKG_APACHE_DEFAULT."
PKG_APACHE_DEFAULT=		apache2
.endif

.for _ap_ in ${PKG_APACHE_ACCEPTED}
.  if empty(_PKG_APACHES:M${_ap_})
PKG_FAIL_REASON+=		"[apache.mk] Invalid apache package \""${_ap_:Q}"\" in PKG_APACHE_ACCEPTED."
PKG_APACHE_ACCEPTED=		# none
.  endif
.endfor

# Mark the acceptable apaches and check which apache packages are installed.
.for _ap_ in ${PKG_APACHE_ACCEPTED}
_APACHE_OK.${_ap_}=	yes
_APACHE_INSTALLED.${_ap_}!= \
	if ${PKG_INFO} -qe ${_APACHE_PKGBASE.${_ap_}}; then		\
		${ECHO} yes;						\
	else								\
		${ECHO} no;						\
	fi
.endfor
.for ap in ${_PKG_APACHES}
_APACHE_OK.${ap}?=	no
.endfor

.undef PKG_APACHE

# Use one of the installed apaches, ...
.for _ap_ in ${PKG_APACHE_ACCEPTED}
.  if ${_APACHE_INSTALLED.${_ap_}} == "yes"
PKG_APACHE?=		${_ap_}
.  endif
.endfor

# ... otherwise, prefer the default one if it's accepted, ...
.if ${_APACHE_OK.${PKG_APACHE_DEFAULT}} == "yes"
PKG_APACHE?=		${PKG_APACHE_DEFAULT}
.endif

# ... otherwise, just use the first accepted apache.
.for ap in ${PKG_APACHE_ACCEPTED}
PKG_APACHE?=		${ap}
.endfor

.if defined(PKG_APACHE)
.  include "${_APACHE_PKGSRCDIR.${PKG_APACHE}}/buildlink3.mk"
.else
PKG_FAIL_REASON+=	"[apache.mk] No acceptable apache package found."
PKG_APACHE=		none
.endif

APACHE_PKG_PREFIX=	${_APACHE_PKG_PREFIX.${PKG_APACHE}}

.if (${PKG_APACHE} == "apache2") && !empty(USE_APR:M[yY][eE][sS])
.  include "../../devel/apr/buildlink3.mk"
.endif

.endif	# APACHE_MK
