/*	$NetBSD: extern.h,v 1.4 2003/09/01 15:31:17 jlam Exp $	*/

/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)extern.h	8.1 (Berkeley) 6/6/93
 */

#include <nbconfig.h>
#include <nbtypes.h>

#include <mtree.h>

#ifdef __NetBSD__
#define HAVE_STRUCT_STAT_ST_FLAGS 1
#endif
 
#if HAVE_ERR_H
#include <err.h> 
#endif

#include <fts.h>

#include <vis.h>

#if HAVE_NETDB_H
/* For MAXHOSTNAMELEN on some platforms. */
#include <netdb.h>
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 256
#endif

#ifndef HAVE_STRSEP
char *strsep(char **, const char *);
#endif

#ifndef HAVE_USER_FROM_UID
char *user_from_uid(uid_t, int);
#endif

#ifndef HAVE_GROUP_FROM_GID
char *group_from_gid(gid_t, int);
#endif

#ifndef HAVE_GETMODE
mode_t getmode(const void *, mode_t);
#endif

#ifndef HAVE_SETMODE
void *setmode(const char *);
#endif

void	 addtag(slist_t *, char *);
int	 check_excludes(const char *, const char *);
int	 compare(NODE *, FTSENT *);
int	 crc(int, u_int32_t *, u_int32_t *);
void	 cwalk(void);
void	 dump_nodes(const char *, NODE *, int);
void	 init_excludes(void);
int	 matchtags(NODE *);
void	 mtree_err(const char *, ...)
	    __attribute__((__format__(__printf__, 1, 2)));
const char *nodetype(u_int);
u_int	 parsekey(const char *, int *);
void	 parsetags(slist_t *, char *);
u_int	 parsetype(const char *);
void	 read_excludes_file(const char *);
const char *rlink(const char *);
int	 verify(void);

extern int	dflag, eflag, iflag, lflag, mflag, rflag, sflag, tflag, uflag;
extern int	Wflag;
extern size_t	mtree_lineno;
extern u_int32_t crc_total;
extern int	ftsoptions, keys;
extern char	fullpath[];
extern slist_t	includetags, excludetags;


#include <stat_flags.h>
