# $NetBSD: builtin.mk,v 1.2 2011/11/30 07:57:09 sbd Exp $

BUILTIN_PKG:=	libuuid

BUILTIN_FIND_FILES_VAR=		H_UUID
BUILTIN_FIND_FILES.H_UUID=	/usr/include/uuid/uuid.h
BUILTIN_FIND_GREP.H_UUID=	uuid_generate
BUILTIN_FIND_LIBS:=		uuid

.include "../../mk/buildlink3/bsd.builtin.mk"

##
## Determine if there is a built-in implementation of the package and
## set IS_BUILTIN.<pkg> appropriately ("yes" or "no").
##
.if !defined(IS_BUILTIN.libuuid)
IS_BUILTIN.libuuid=	no
.  if !empty(BUILTIN_LIB_FOUND.uuid:M[yY][eE][sS]) && \
      empty(H_UUID:M__nonexistent__)
IS_BUILTIN.libuuid=	yes
.  endif
.endif
MAKEVARS+=	IS_BUILTIN.libuuid

###
### If there is a built-in implementation, then set BUILTIN_PKG.<pkg> to
### a package name to represent the built-in package.
###
.if !defined(BUILTIN_PKG.libuuid) && \
    !empty(IS_BUILTIN.libuuid:M[yY][eE][sS])
BUILTIN_PKG.libuuid=	libuuid-2.18	# whatever, as long as it is big enough
.endif

###
### Determine whether we should use the built-in implementation if it
### exists, and set USE_BUILTIN.<pkg> appropriate ("yes" or "no").
###
.if !defined(USE_BUILTIN.libuuid)
.  if ${PREFER.libuuid} == "pkgsrc"
USE_BUILTIN.libuuid=       no
.  else
USE_BUILTIN.libuuid=       ${IS_BUILTIN.libuuid}
.    if defined(BUILTIN_PKG.libuuid) && \
        !empty(IS_BUILTIN.libuuid:M[yY][eE][sS])
USE_BUILTIN.libuuid=       yes
.      for _dep_ in ${BUILDLINK_API_DEPENDS.libuuid}
.        if !empty(USE_BUILTIN.libuuid:M[yY][eE][sS])
USE_BUILTIN.libuuid!=      \
	if ${PKG_ADMIN} pmatch ${_dep_:Q} ${BUILTIN_PKG.libuuid:Q}; then \
		${ECHO} yes;						\
	else								\
		${ECHO} no;						\
	fi
.        endif
.      endfor
.    endif
.  endif
.endif
MAKEVARS+=	USE_BUILTIN.libuuid

###
### The section below only applies if we are not including this file
### solely to determine whether a built-in implementation exists.
###
CHECK_BUILTIN.libuuid?=	no
.if !empty(CHECK_BUILTIN.libuuid:M[nN][oO])
.  if !empty(USE_BUILTIN.libuuid:M[yY][eE][sS]) && \
      !empty(USE_TOOLS:C/:.*//:Mpkg-config)
BUILDLINK_TARGETS+=	libuuid-fake-pc

libuuid-fake-pc:
	${RUN}						\
	${MKDIR} ${BUILDLINK_DIR}/lib/pkgconfig;	\
	{	${ECHO} "Name: uuid";				\
		${ECHO} "Description: Universally unique id library"; \
		${ECHO} "Version: ${BUILTIN_VERSION.libuuid}";	\
		${ECHO} "Libs: -L/usr/lib -luuid"		\
		${ECHO} "Cflags: -I/usr/include";		\
	} >${BUILDLINK_DIR}/lib/pkgconfig/uuid.pc
.  endif
.endif # CHECK_BUILTIN.libuuid
