# $NetBSD: dlopen.builtin.mk,v 1.1 2004/11/26 07:05:19 jlam Exp $

.for _lib_ in dl
.  if !defined(_BLNK_LIB_FOUND.${_lib_})
_BLNK_LIB_FOUND.${_lib_}!=	\
	if ${TEST} "`${ECHO} /usr/lib/lib${_lib_}.*`" = "/usr/lib/lib${_lib_}.*"; then \
		${ECHO} "no";						\
	elif ${TEST} "`${ECHO} /lib/lib${_lib_}.*`" = "/lib/lib${_lib_}.*"; then \
		${ECHO} "no";						\
	else								\
		${ECHO} "yes";						\
	fi
BUILDLINK_VARS+=	_BLNK_LIB_FOUND.${_lib_}
.  endif
.endfor
.undef _lib_

.if !defined(IS_BUILTIN.dl)
IS_BUILTIN.dl=		no
.  if exists(/usr/include/dlfcn.h)
IS_BUILTIN.dl=		yes
.  endif
BUILDLINK_VARS+=	IS_BUILTIN.dl
.endif	# IS_BUILTIN.pthread

.if !defined(USE_BUILTIN.dl)
USE_BUILTIN.dl=		${IS_BUILTIN.dl}
.  if ${OPSYS} == "Darwin"
USE_BUILTIN.dl=		no	# Darwin uses devel/dlcompat
.  endif
.endif

CHECK_BUILTIN.dl?=	no
.if !empty(CHECK_BUILTIN.dl:M[nN][oO])

.  if !empty(USE_BUILTIN.dl:M[yY][eE][sS])
BUILDLINK_PREFIX.dl=	/usr
.    if !empty(_BLNK_LIB_FOUND.dl:M[yY][eE][sS])
BUILDLINK_LIBS.dl=	-ldl
.    endif
#
# The following platforms require pthreads to be linked into the
# application if it uses dlopen() or else the applications will core
# dump when they dlopen a shared module that _is_ linked with pthread
# support.
#
_DLOPEN_REQUIRE_PTHREAD_PLATFORMS=					\
	NetBSD-2.[0-9]-* NetBSD-2.[0-8][0-9]*-* NetBSD-2.9[0-8]*-*	\
	NetBSD-2.99.[0-9]-* NetBSD-2.99.10-*

_DLOPEN_REQUIRE_PTHREADS?=	no
.    for _pattern_ in ${_DLOPEN_REQUIRE_PTHREAD_PLATFORMS}
.      if !empty(MACHINE_PLATFORM:M${_pattern_})
.        if !empty(PREFER_NATIVE_PTHREADS:M[yY][eE][sS])
_DLOPEN_REQUIRE_PTHREADS=	yes
.        endif
.      endif
.    endfor
#
# DLOPEN_REQUIRE_PTHREADS is a user- and package-settable yes/no variable
#	whose value decides whether pthread.buildlink3.mk is automatically
#	included or not.  Its default value depends on whether native
#	pthreads exist.
#
# Including pthread.buildlink3.mk is deferred until bsd.pkg.mk.
#
.    if defined(DLOPEN_REQUIRE_PTHREADS)
_DLOPEN_REQUIRE_PTHREADS:=      ${DLOPEN_REQUIRE_PTHREADS}
.    else
DLOPEN_REQUIRE_PTHREADS=        ${_DLOPEN_REQUIRE_PTHREADS}
.    endif
.    if !empty(_DLOPEN_REQUIRE_PTHREADS:M[yY][eE][sS])
BUILDLINK_CFLAGS.dl+=	${PTHREAD_CFLAGS}
BUILDLINK_LDFLAGS.dl+=	${PTHREAD_LDFLAGS}
BUILDLINK_LIBS.dl+=	${PTHREAD_LIBS}
.    endif
.  endif # USE_BUILTIN.dl == yes

.endif	# CHECK_BUILTIN.dl
