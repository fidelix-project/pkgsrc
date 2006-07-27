# $NetBSD: fetch-list.mk,v 1.7 2006/07/27 17:23:16 jlam Exp $

# Prints out a script to fetch all needed files (no checksumming).
.PHONY: fetch-list
fetch-list: fetch-list-header fetch-list-recursive

.PHONY: fetch-list-header
fetch-list-header:
	@${ECHO} '#!/bin/sh'
	@${ECHO} '#'
	@${ECHO} '# This is an auto-generated script, the result of running'
	@${ECHO} '# `${MAKE} fetch-list'"'"' in directory "'"`${PWD_CMD}`"'"'
	@${ECHO} '# on host "'"`${UNAME} -n`"'" on "'"`date`"'".'
	@${ECHO} '#'

.PHONY: fetch-list-recursive
fetch-list-recursive:
	@${_DEPENDS_WALK_CMD} -r ${PKGPATH} |				\
	while read dir; do						\
	    (	cd ../../$$dir && ${SETENV} ${PKGSRC_MAKE_ENV}		\
		${MAKE} ${MAKEFLAGS} fetch-list-one-pkg |		\
		${AWK} '/^[^#]/ { FoundSomething = 1 }			\
			/^unsorted/ { gsub(/[[:space:]]+/, " \\\n\t") }	\
			/^echo/ { gsub(/;[[:space:]]+/, "\n") }		\
			{ block[line_c++] = $$0 }			\
			END { if (FoundSomething)			\
				for (line = 0; line < line_c; line++)	\
					print block[line] }'		\
	    );								\
	done

.PHONY: fetch-list-one-pkg
fetch-list-one-pkg:
.if !empty(_ALLFILES)
	@${ECHO}
	@${ECHO} '#'
	@location=`${PWD_CMD} | ${AWK} -F / '{ print $$(NF-1) "/" $$NF }'`; \
		${ECHO} '# Need additional files for ${PKGNAME} ('$$location')...'
.  for fetchfile in ${_ALLFILES}
.    if exists(${DYNAMIC_SITES_SCRIPT})
	@(if [ ! -f ${_DISTDIR}/${fetchfile:T} ]; then			\
		${ECHO};						\
		filesize=`${AWK} '					\
			/^Size/ && $$2 == "(${fetchfile})" { print $$4 } \
			' ${DISTINFO_FILE}` || true;			\
		${ECHO} '# Fetch ${fetchfile} ('$${filesize-???}' bytes):'; \
		${ECHO} '#';						\
		${ECHO} '${SH} -s ${fetchfile:T} <<"EOF" |(';		\
		${CAT} ${DYNAMIC_SITES_SCRIPT};				\
		${ECHO} EOF;						\
		${ECHO} read unsorted_sites;				\
		${ECHO} 'unsorted_sites="$${unsorted_sites} ${_MASTER_SITE_BACKUP}"'; \
		${ECHO} sites='"'${_ORDERED_SITES:Q}'"';		\
		${ECHO} "${MKDIR} ${_DISTDIR}";				\
		${ECHO} 'cd ${_DISTDIR} && [ -f ${fetchfile} -o -f ${fetchfile:T} ] ||'; \
		${ECHO}	'for site in $$sites; do';			\
		${ECHO} '	${FETCH_CMD} ${FETCH_BEFORE_ARGS} "$${site}${fetchfile:T}" ${FETCH_AFTER_ARGS} && break ||'; \
		${ECHO} '	${ECHO} ${fetchfile:T} not fetched';	\
		${ECHO}	done;						\
		${ECHO} ')';						\
	fi)
.    else
	@(if [ ! -f ${_DISTDIR}/${fetchfile:T} ]; then			\
		${ECHO};						\
		filesize=`${AWK} '					\
			/^Size/ && $$2 == "(${fetchfile})" { print $$4 } \
			' ${DISTINFO_FILE}` || true;			\
		${ECHO} '# Fetch ${fetchfile} ('$${filesize-???}' bytes):'; \
		${ECHO} '#';						\
		${ECHO} 'unsorted_sites="${SITES.${fetchfile:T:S/=/--/}} ${_MASTER_SITE_BACKUP}"'; \
		${ECHO} sites='"'${_ORDERED_SITES:Q}'"';		\
		${ECHO} "${MKDIR} ${_DISTDIR}";				\
		${ECHO} 'cd ${_DISTDIR} && [ -f ${fetchfile} -o -f ${fetchfile:T} ] ||'; \
		${ECHO}	'for site in $$sites; do';			\
		${ECHO} '	${FETCH_CMD} ${FETCH_BEFORE_ARGS} "$${site}${fetchfile:T}" ${FETCH_AFTER_ARGS} && break ||'; \
		${ECHO} '	${ECHO} ${fetchfile:T} not fetched';	\
		${ECHO}	done;						\
	fi)
.    endif
.  endfor
.endif
