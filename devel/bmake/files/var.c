/*	$NetBSD: var.c,v 1.2 2005/12/02 00:14:56 sjg Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
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
 */

/*
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
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
 */

#ifndef MAKE_NATIVE
static char rcsid[] = "$NetBSD: var.c,v 1.2 2005/12/02 00:14:56 sjg Exp $";
#else
#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)var.c	8.3 (Berkeley) 3/19/94";
#else
__RCSID("$NetBSD: var.c,v 1.2 2005/12/02 00:14:56 sjg Exp $");
#endif
#endif /* not lint */
#endif

/*-
 * var.c --
 *	Variable-handling functions
 *
 * Interface:
 *	Var_Set	  	    Set the value of a variable in the given
 *	    	  	    context. The variable is created if it doesn't
 *	    	  	    yet exist. The value and variable name need not
 *	    	  	    be preserved.
 *
 *	Var_Append	    Append more characters to an existing variable
 *	    	  	    in the given context. The variable needn't
 *	    	  	    exist already -- it will be created if it doesn't.
 *	    	  	    A space is placed between the old value and the
 *	    	  	    new one.
 *
 *	Var_Exists	    See if a variable exists.
 *
 *	Var_Value 	    Return the value of a variable in a context or
 *	    	  	    NULL if the variable is undefined.
 *
 *	Var_Subst 	    Substitute named variable, or all variables if
 *			    NULL in a string using
 *	    	  	    the given context as the top-most one. If the
 *	    	  	    third argument is non-zero, Parse_Error is
 *	    	  	    called if any variables are undefined.
 *
 *	Var_Parse 	    Parse a variable expansion from a string and
 *	    	  	    return the result and the number of characters
 *	    	  	    consumed.
 *
 *	Var_Delete	    Delete a variable in a context.
 *
 *	Var_Init  	    Initialize this module.
 *
 * Debugging:
 *	Var_Dump  	    Print out all variables defined in the given
 *	    	  	    context.
 *
 * XXX: There's a lot of duplication in these functions.
 */

#ifndef NO_REGEX
#include    <sys/types.h>
#include    <nbcompat/nbconfig.h>
/* bmake supplies its own <sys/cdefs.h> so this header is always present. */
#ifndef HAVE_SYS_CDEFS_H
#define HAVE_SYS_CDEFS_H 1
#endif
#if HAVE_REGEX_H
#include    <regex.h>
#else
#include    <nbcompat/regex.h>
#endif
#endif
#include    <ctype.h>
#include    <stdlib.h>
#include    <limits.h>

#include    "make.h"
#include    "buf.h"

/*
 * This is a harmless return value for Var_Parse that can be used by Var_Subst
 * to determine if there was an error in parsing -- easier than returning
 * a flag, as things outside this module don't give a hoot.
 */
char 	var_Error[] = "";

/*
 * Similar to var_Error, but returned when the 'err' flag for Var_Parse is
 * set false. Why not just use a constant? Well, gcc likes to condense
 * identical string instances...
 */
static char	varNoError[] = "";

/*
 * Internally, variables are contained in four different contexts.
 *	1) the environment. They may not be changed. If an environment
 *	    variable is appended-to, the result is placed in the global
 *	    context.
 *	2) the global context. Variables set in the Makefile are located in
 *	    the global context. It is the penultimate context searched when
 *	    substituting.
 *	3) the command-line context. All variables set on the command line
 *	   are placed in this context. They are UNALTERABLE once placed here.
 *	4) the local context. Each target has associated with it a context
 *	   list. On this list are located the structures describing such
 *	   local variables as $(@) and $(*)
 * The four contexts are searched in the reverse order from which they are
 * listed.
 */
GNode          *VAR_GLOBAL;   /* variables from the makefile */
GNode          *VAR_CMD;      /* variables defined on the command-line */

#define FIND_CMD	0x1   /* look in VAR_CMD when searching */
#define FIND_GLOBAL	0x2   /* look in VAR_GLOBAL as well */
#define FIND_ENV  	0x4   /* look in the environment also */

typedef struct Var {
    char          *name;	/* the variable's name */
    Buffer	  val;	    	/* its value */
    int	    	  flags;    	/* miscellaneous status flags */
#define VAR_IN_USE	1   	    /* Variable's value currently being used.
				     * Used to avoid recursion */
#define VAR_FROM_ENV	2   	    /* Variable comes from the environment */
#define VAR_JUNK  	4   	    /* Variable is a junk variable that
				     * should be destroyed when done with
				     * it. Used by Var_Parse for undefined,
				     * modified variables */
#define VAR_KEEP	8	    /* Variable is VAR_JUNK, but we found
				     * a use for it in some modifier and
				     * the value is therefore valid */
}  Var;


/* Var*Pattern flags */
#define VAR_SUB_GLOBAL	0x01	/* Apply substitution globally */
#define VAR_SUB_ONE	0x02	/* Apply substitution to one word */
#define VAR_SUB_MATCHED	0x04	/* There was a match */
#define VAR_MATCH_START	0x08	/* Match at start of word */
#define VAR_MATCH_END	0x10	/* Match at end of word */
#define VAR_NOSUBST	0x20	/* don't expand vars in VarGetPattern */

/* Var_Set flags */
#define VAR_NO_EXPORT	0x01	/* do not export */

typedef struct {
    /*
     * The following fields are set by Var_Parse() when it
     * encounters modifiers that need to keep state for use by
     * subsequent modifiers within the same variable expansion.
     */
    Byte	varSpace;	/* Word separator in expansions */
    Boolean	oneBigWord;	/* TRUE if we will treat the variable as a
				 * single big word, even if it contains
				 * embedded spaces (as opposed to the
				 * usual behaviour of treating it as
				 * several space-separated words). */
} Var_Parse_State;

/* struct passed as ClientData to VarSubstitute() for ":S/lhs/rhs/",
 * to VarSYSVMatch() for ":lhs=rhs". */
typedef struct {
    const char   *lhs;	    /* String to match */
    int	    	  leftLen; /* Length of string */
    const char   *rhs;	    /* Replacement string (w/ &'s removed) */
    int	    	  rightLen; /* Length of replacement */
    int	    	  flags;
} VarPattern;

/* struct passed as ClientData to VarLoopExpand() for ":@tvar@str@" */
typedef struct {
    GNode	*ctxt;		/* variable context */
    char	*tvar;		/* name of temp var */
    int		tvarLen;	
    char	*str;		/* string to expand */
    int		strLen;		
    int		err;		/* err for not defined */
} VarLoop_t;

#ifndef NO_REGEX
/* struct passed as ClientData to VarRESubstitute() for ":C///" */
typedef struct {
    regex_t	   re;
    int		   nsub;
    regmatch_t 	  *matches;
    char 	  *replace;
    int		   flags;
} VarREPattern;
#endif

/* struct passed to VarSelectWords() for ":[start..end]" */
typedef struct {
    int		start;		/* first word to select */
    int		end;		/* last word to select */
} VarSelectWords_t;

static Var *VarFind(const char *, GNode *, int);
static void VarAdd(const char *, const char *, GNode *);
static Boolean VarHead(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarTail(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarSuffix(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarRoot(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarMatch(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
#ifdef SYSVVARSUB
static Boolean VarSYSVMatch(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
#endif
static Boolean VarNoMatch(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
#ifndef NO_REGEX
static void VarREError(int, regex_t *, const char *);
static Boolean VarRESubstitute(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
#endif
static Boolean VarSubstitute(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static Boolean VarLoopExpand(GNode *, Var_Parse_State *,
			char *, Boolean, Buffer, ClientData);
static char *VarGetPattern(GNode *, Var_Parse_State *,
			   int, const char **, int, int *, int *,
			   VarPattern *);
static char *VarQuote(char *);
static char *VarChangeCase(char *, int);
static char *VarModify(GNode *, Var_Parse_State *,
    const char *,
    Boolean (*)(GNode *, Var_Parse_State *, char *, Boolean, Buffer, ClientData),
    ClientData);
static char *VarOrder(const char *, const char);
static char *VarUniq(const char *);
static int VarWordCompare(const void *, const void *);
static void VarPrintVar(ClientData);

#define WR(a)	((char *)UNCONST(a))

#define BROPEN	'{'
#define BRCLOSE	'}'
#define PROPEN	'('
#define PRCLOSE	')'

/*-
 *-----------------------------------------------------------------------
 * VarFind --
 *	Find the given variable in the given context and any other contexts
 *	indicated.
 *
 * Input:
 *	name		name to find
 *	ctxt		context in which to find it
 *	flags		FIND_GLOBAL set means to look in the
 *			VAR_GLOBAL context as well. FIND_CMD set means
 *			to look in the VAR_CMD context also. FIND_ENV
 *			set means to look in the environment
 *
 * Results:
 *	A pointer to the structure describing the desired variable or
 *	NIL if the variable does not exist.
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
static Var *
VarFind(const char *name, GNode *ctxt, int flags)
{
    Hash_Entry         	*var;
    Var		  	*v;

	/*
	 * If the variable name begins with a '.', it could very well be one of
	 * the local ones.  We check the name against all the local variables
	 * and substitute the short version in for 'name' if it matches one of
	 * them.
	 */
	if (*name == '.' && isupper((unsigned char) name[1]))
		switch (name[1]) {
		case 'A':
			if (!strcmp(name, ".ALLSRC"))
				name = ALLSRC;
			if (!strcmp(name, ".ARCHIVE"))
				name = ARCHIVE;
			break;
		case 'I':
			if (!strcmp(name, ".IMPSRC"))
				name = IMPSRC;
			break;
		case 'M':
			if (!strcmp(name, ".MEMBER"))
				name = MEMBER;
			break;
		case 'O':
			if (!strcmp(name, ".OODATE"))
				name = OODATE;
			break;
		case 'P':
			if (!strcmp(name, ".PREFIX"))
				name = PREFIX;
			break;
		case 'T':
			if (!strcmp(name, ".TARGET"))
				name = TARGET;
			break;
		}
    /*
     * First look for the variable in the given context. If it's not there,
     * look for it in VAR_CMD, VAR_GLOBAL and the environment, in that order,
     * depending on the FIND_* flags in 'flags'
     */
    var = Hash_FindEntry(&ctxt->context, name);

    if ((var == NULL) && (flags & FIND_CMD) && (ctxt != VAR_CMD)) {
	var = Hash_FindEntry(&VAR_CMD->context, name);
    }
    if (!checkEnvFirst && (var == NULL) && (flags & FIND_GLOBAL) &&
	(ctxt != VAR_GLOBAL))
    {
	var = Hash_FindEntry(&VAR_GLOBAL->context, name);
    }
    if ((var == NULL) && (flags & FIND_ENV)) {
	char *env;

	if ((env = getenv(name)) != NULL) {
	    int	  	len;

	    v = emalloc(sizeof(Var));
	    v->name = estrdup(name);

	    len = strlen(env);

	    v->val = Buf_Init(len);
	    Buf_AddBytes(v->val, len, (Byte *)env);

	    v->flags = VAR_FROM_ENV;
	    return (v);
	} else if (checkEnvFirst && (flags & FIND_GLOBAL) &&
		   (ctxt != VAR_GLOBAL))
	{
	    var = Hash_FindEntry(&VAR_GLOBAL->context, name);
	    if (var == NULL) {
		return ((Var *)NIL);
	    } else {
		return ((Var *)Hash_GetValue(var));
	    }
	} else {
	    return((Var *)NIL);
	}
    } else if (var == NULL) {
	return ((Var *)NIL);
    } else {
	return ((Var *)Hash_GetValue(var));
    }
}

/*-
 *-----------------------------------------------------------------------
 * VarAdd  --
 *	Add a new variable of name name and value val to the given context
 *
 * Input:
 *	name		name of variable to add
 *	val		value to set it to
 *	ctxt		context in which to set it
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The new variable is placed at the front of the given context
 *	The name and val arguments are duplicated so they may
 *	safely be freed.
 *-----------------------------------------------------------------------
 */
static void
VarAdd(const char *name, const char *val, GNode *ctxt)
{
    Var   	  *v;
    int	    	  len;
    Hash_Entry    *h;

    v = emalloc(sizeof(Var));

    len = val ? strlen(val) : 0;
    v->val = Buf_Init(len+1);
    Buf_AddBytes(v->val, len, (const Byte *)val);

    v->flags = 0;

    h = Hash_CreateEntry(&ctxt->context, name, NULL);
    Hash_SetValue(h, v);
    v->name = h->name;
    if (DEBUG(VAR)) {
	printf("%s:%s = %s\n", ctxt->name, name, val);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Var_Delete --
 *	Remove a variable from a context.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The Var structure is removed and freed.
 *
 *-----------------------------------------------------------------------
 */
void
Var_Delete(const char *name, GNode *ctxt)
{
    Hash_Entry 	  *ln;

    if (DEBUG(VAR)) {
	printf("%s:delete %s\n", ctxt->name, name);
    }
    ln = Hash_FindEntry(&ctxt->context, name);
    if (ln != NULL) {
	Var 	  *v;

	v = (Var *)Hash_GetValue(ln);
	if (v->name != ln->name)
		free(v->name);
	Hash_DeleteEntry(&ctxt->context, ln);
	Buf_Destroy(v->val, TRUE);
	free(v);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Var_Set --
 *	Set the variable name to the value val in the given context.
 *
 * Input:
 *	name		name of variable to set
 *	val		value to give to the variable
 *	ctxt		context in which to set it
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	If the variable doesn't yet exist, a new record is created for it.
 *	Else the old value is freed and the new one stuck in its place
 *
 * Notes:
 *	The variable is searched for only in its context before being
 *	created in that context. I.e. if the context is VAR_GLOBAL,
 *	only VAR_GLOBAL->context is searched. Likewise if it is VAR_CMD, only
 *	VAR_CMD->context is searched. This is done to avoid the literally
 *	thousands of unnecessary strcmp's that used to be done to
 *	set, say, $(@) or $(<).
 *-----------------------------------------------------------------------
 */
void
Var_Set(const char *name, const char *val, GNode *ctxt, int flags)
{
    Var   *v;
    const char *cp = name;
    
    /*
     * We only look for a variable in the given context since anything set
     * here will override anything in a lower context, so there's not much
     * point in searching them all just to save a bit of memory...
     */
    if ((name = strchr(cp, '$'))) {
	name = Var_Subst(NULL, cp, ctxt, 0);
    } else
	name = cp;
    v = VarFind(name, ctxt, 0);
    if (v == (Var *)NIL) {
	VarAdd(name, val, ctxt);
    } else {
	Buf_Discard(v->val, Buf_Size(v->val));
	Buf_AddBytes(v->val, strlen(val), (const Byte *)val);

	if (DEBUG(VAR)) {
	    printf("%s:%s = %s\n", ctxt->name, name, val);
	}
    }
    /*
     * Any variables given on the command line are automatically exported
     * to the environment (as per POSIX standard)
     */
    if (ctxt == VAR_CMD && (flags & VAR_NO_EXPORT) == 0) {

	/*
	 * If requested, don't export these in the environment
	 * individually.  We still put them in MAKEOVERRIDES so
	 * that the command-line settings continue to override
	 * Makefile settings.
	 */
	if (varNoExportEnv != TRUE)
	    setenv(name, val, 1);

	Var_Append(MAKEOVERRIDES, name, VAR_GLOBAL);
    }
    if (name != cp)
	free(UNCONST(name));
}

/*-
 *-----------------------------------------------------------------------
 * Var_Append --
 *	The variable of the given name has the given value appended to it in
 *	the given context.
 *
 * Input:
 *	name		name of variable to modify
 *	val		String to append to it
 *	ctxt		Context in which this should occur
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	If the variable doesn't exist, it is created. Else the strings
 *	are concatenated (with a space in between).
 *
 * Notes:
 *	Only if the variable is being sought in the global context is the
 *	environment searched.
 *	XXX: Knows its calling circumstances in that if called with ctxt
 *	an actual target, it will only search that context since only
 *	a local variable could be being appended to. This is actually
 *	a big win and must be tolerated.
 *-----------------------------------------------------------------------
 */
void
Var_Append(const char *name, const char *val, GNode *ctxt)
{
    Var		   *v;
    Hash_Entry	   *h;
    const char *cp = name;

    if ((name = strchr(cp, '$'))) {
	name = Var_Subst(NULL, cp, ctxt, 0);
    } else
	name = cp;
    
    v = VarFind(name, ctxt, (ctxt == VAR_GLOBAL) ? FIND_ENV : 0);

    if (v == (Var *)NIL) {
	VarAdd(name, val, ctxt);
    } else {
	Buf_AddByte(v->val, (Byte)' ');
	Buf_AddBytes(v->val, strlen(val), (const Byte *)val);

	if (DEBUG(VAR)) {
	    printf("%s:%s = %s\n", ctxt->name, name,
		   (char *)Buf_GetAll(v->val, NULL));
	}

	if (v->flags & VAR_FROM_ENV) {
	    /*
	     * If the original variable came from the environment, we
	     * have to install it in the global context (we could place
	     * it in the environment, but then we should provide a way to
	     * export other variables...)
	     */
	    v->flags &= ~VAR_FROM_ENV;
	    h = Hash_CreateEntry(&ctxt->context, name, NULL);
	    Hash_SetValue(h, v);
	}
    }
    if (name != cp)
	free(UNCONST(name));
}

/*-
 *-----------------------------------------------------------------------
 * Var_Exists --
 *	See if the given variable exists.
 *
 * Input:
 *	name		Variable to find
 *	ctxt		Context in which to start search
 *
 * Results:
 *	TRUE if it does, FALSE if it doesn't
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Boolean
Var_Exists(const char *name, GNode *ctxt)
{
    Var	    	  *v;

    v = VarFind(name, ctxt, FIND_CMD|FIND_GLOBAL|FIND_ENV);

    if (v == (Var *)NIL) {
	return(FALSE);
    } else if (v->flags & VAR_FROM_ENV) {
	free(v->name);
	Buf_Destroy(v->val, TRUE);
	free(v);
    }
    return(TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * Var_Value --
 *	Return the value of the named variable in the given context
 *
 * Input:
 *	name		name to find
 *	ctxt		context in which to search for it
 *
 * Results:
 *	The value if the variable exists, NULL if it doesn't
 *
 * Side Effects:
 *	None
 *-----------------------------------------------------------------------
 */
char *
Var_Value(const char *name, GNode *ctxt, char **frp)
{
    Var            *v;

    v = VarFind(name, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
    *frp = NULL;
    if (v != (Var *)NIL) {
	char *p = ((char *)Buf_GetAll(v->val, NULL));
	if (v->flags & VAR_FROM_ENV) {
	    free(v->name);
	    Buf_Destroy(v->val, FALSE);
	    free(v);
	    *frp = p;
	}
	return p;
    } else {
	return (NULL);
    }
}

/*-
 *-----------------------------------------------------------------------
 * VarHead --
 *	Remove the tail of the given word and place the result in the given
 *	buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	True if need to add a space to the buffer
 *			before sticking in the head
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarHead(GNode *ctx __unused, Var_Parse_State *vpstate,
	char *word, Boolean addSpace, Buffer buf,
	ClientData dummy)
{
    char *slash;

    slash = strrchr(word, '/');
    if (slash != NULL) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte(buf, vpstate->varSpace);
	}
	*slash = '\0';
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
	*slash = '/';
	return (TRUE);
    } else {
	/*
	 * If no directory part, give . (q.v. the POSIX standard)
	 */
	if (addSpace && vpstate->varSpace)
	    Buf_AddByte(buf, vpstate->varSpace);
	Buf_AddByte(buf, (Byte)'.');
    }
    return(dummy ? TRUE : TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * VarTail --
 *	Remove the head of the given word and place the result in the given
 *	buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	True if need to add a space to the buffer
 *			before adding the tail
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarTail(GNode *ctx __unused, Var_Parse_State *vpstate,
	char *word, Boolean addSpace, Buffer buf,
	ClientData dummy)
{
    char *slash;

    if (addSpace && vpstate->varSpace) {
	Buf_AddByte(buf, vpstate->varSpace);
    }

    slash = strrchr(word, '/');
    if (slash != NULL) {
	*slash++ = '\0';
	Buf_AddBytes(buf, strlen(slash), (Byte *)slash);
	slash[-1] = '/';
    } else {
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return (dummy ? TRUE : TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * VarSuffix --
 *	Place the suffix of the given word in the given buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	TRUE if need to add a space before placing the
 *			suffix in the buffer
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The suffix from the word is placed in the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarSuffix(GNode *ctx __unused, Var_Parse_State *vpstate,
	  char *word, Boolean addSpace, Buffer buf,
	  ClientData dummy)
{
    char *dot;

    dot = strrchr(word, '.');
    if (dot != NULL) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte(buf, vpstate->varSpace);
	}
	*dot++ = '\0';
	Buf_AddBytes(buf, strlen(dot), (Byte *)dot);
	dot[-1] = '.';
	addSpace = TRUE;
    }
    return (dummy ? addSpace : addSpace);
}

/*-
 *-----------------------------------------------------------------------
 * VarRoot --
 *	Remove the suffix of the given word and place the result in the
 *	buffer.
 *
 * Input:
 *	word		Word to trim
 *	addSpace	TRUE if need to add a space to the buffer
 *			before placing the root in it
 *	buf		Buffer in which to store it
 *
 * Results:
 *	TRUE if characters were added to the buffer (a space needs to be
 *	added to the buffer before the next word).
 *
 * Side Effects:
 *	The trimmed word is added to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarRoot(GNode *ctx __unused, Var_Parse_State *vpstate,
	char *word, Boolean addSpace, Buffer buf,
	ClientData dummy)
{
    char *dot;

    if (addSpace && vpstate->varSpace) {
	Buf_AddByte(buf, vpstate->varSpace);
    }

    dot = strrchr(word, '.');
    if (dot != NULL) {
	*dot = '\0';
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
	*dot = '.';
    } else {
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return (dummy ? TRUE : TRUE);
}

/*-
 *-----------------------------------------------------------------------
 * VarMatch --
 *	Place the word in the buffer if it matches the given pattern.
 *	Callback function for VarModify to implement the :M modifier.
 *
 * Input:
 *	word		Word to examine
 *	addSpace	TRUE if need to add a space to the buffer
 *			before adding the word, if it matches
 *	buf		Buffer in which to store it
 *	pattern		Pattern the word must match
 *
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarMatch(GNode *ctx __unused, Var_Parse_State *vpstate,
	 char *word, Boolean addSpace, Buffer buf,
	 ClientData pattern)
{
    if (Str_Match(word, (char *)pattern)) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte(buf, vpstate->varSpace);
	}
	addSpace = TRUE;
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return(addSpace);
}

#ifdef SYSVVARSUB
/*-
 *-----------------------------------------------------------------------
 * VarSYSVMatch --
 *	Place the word in the buffer if it matches the given pattern.
 *	Callback function for VarModify to implement the System V %
 *	modifiers.
 *
 * Input:
 *	word		Word to examine
 *	addSpace	TRUE if need to add a space to the buffer
 *			before adding the word, if it matches
 *	buf		Buffer in which to store it
 *	patp		Pattern the word must match
 *
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarSYSVMatch(GNode *ctx, Var_Parse_State *vpstate,
	     char *word, Boolean addSpace, Buffer buf,
	     ClientData patp)
{
    int len;
    char *ptr;
    VarPattern 	  *pat = (VarPattern *)patp;
    char *varexp;

    if (addSpace && vpstate->varSpace)
	Buf_AddByte(buf, vpstate->varSpace);

    addSpace = TRUE;

    if ((ptr = Str_SYSVMatch(word, pat->lhs, &len)) != NULL) {
        varexp = Var_Subst(NULL, pat->rhs, ctx, 0);
	Str_SYSVSubst(buf, varexp, ptr, len);
	free(varexp);
    } else {
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }

    return(addSpace);
}
#endif


/*-
 *-----------------------------------------------------------------------
 * VarNoMatch --
 *	Place the word in the buffer if it doesn't match the given pattern.
 *	Callback function for VarModify to implement the :N modifier.
 *
 * Input:
 *	word		Word to examine
 *	addSpace	TRUE if need to add a space to the buffer
 *			before adding the word, if it matches
 *	buf		Buffer in which to store it
 *	pattern		Pattern the word must match
 *
 * Results:
 *	TRUE if a space should be placed in the buffer before the next
 *	word.
 *
 * Side Effects:
 *	The word may be copied to the buffer.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarNoMatch(GNode *ctx __unused, Var_Parse_State *vpstate,
	   char *word, Boolean addSpace, Buffer buf,
	   ClientData pattern)
{
    if (!Str_Match(word, (char *)pattern)) {
	if (addSpace && vpstate->varSpace) {
	    Buf_AddByte(buf, vpstate->varSpace);
	}
	addSpace = TRUE;
	Buf_AddBytes(buf, strlen(word), (Byte *)word);
    }
    return(addSpace);
}


/*-
 *-----------------------------------------------------------------------
 * VarSubstitute --
 *	Perform a string-substitution on the given word, placing the
 *	result in the passed buffer.
 *
 * Input:
 *	word		Word to modify
 *	addSpace	True if space should be added before
 *			other characters
 *	buf		Buffer for result
 *	patternp	Pattern for substitution
 *
 * Results:
 *	TRUE if a space is needed before more characters are added.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarSubstitute(GNode *ctx __unused, Var_Parse_State *vpstate,
	      char *word, Boolean addSpace, Buffer buf,
	      ClientData patternp)
{
    int  	wordLen;    /* Length of word */
    char 	*cp;	    /* General pointer */
    VarPattern	*pattern = (VarPattern *)patternp;

    wordLen = strlen(word);
    if ((pattern->flags & (VAR_SUB_ONE|VAR_SUB_MATCHED)) !=
	(VAR_SUB_ONE|VAR_SUB_MATCHED)) {
	/*
	 * Still substituting -- break it down into simple anchored cases
	 * and if none of them fits, perform the general substitution case.
	 */
	if ((pattern->flags & VAR_MATCH_START) &&
	    (strncmp(word, pattern->lhs, pattern->leftLen) == 0)) {
		/*
		 * Anchored at start and beginning of word matches pattern
		 */
		if ((pattern->flags & VAR_MATCH_END) &&
		    (wordLen == pattern->leftLen)) {
			/*
			 * Also anchored at end and matches to the end (word
			 * is same length as pattern) add space and rhs only
			 * if rhs is non-null.
			 */
			if (pattern->rightLen != 0) {
			    if (addSpace && vpstate->varSpace) {
				Buf_AddByte(buf, vpstate->varSpace);
			    }
			    addSpace = TRUE;
			    Buf_AddBytes(buf, pattern->rightLen,
					 (const Byte *)pattern->rhs);
			}
			pattern->flags |= VAR_SUB_MATCHED;
		} else if (pattern->flags & VAR_MATCH_END) {
		    /*
		     * Doesn't match to end -- copy word wholesale
		     */
		    goto nosub;
		} else {
		    /*
		     * Matches at start but need to copy in trailing characters
		     */
		    if ((pattern->rightLen + wordLen - pattern->leftLen) != 0){
			if (addSpace && vpstate->varSpace) {
			    Buf_AddByte(buf, vpstate->varSpace);
			}
			addSpace = TRUE;
		    }
		    Buf_AddBytes(buf, pattern->rightLen,
			(const Byte *)pattern->rhs);
		    Buf_AddBytes(buf, wordLen - pattern->leftLen,
				 (Byte *)(word + pattern->leftLen));
		    pattern->flags |= VAR_SUB_MATCHED;
		}
	} else if (pattern->flags & VAR_MATCH_START) {
	    /*
	     * Had to match at start of word and didn't -- copy whole word.
	     */
	    goto nosub;
	} else if (pattern->flags & VAR_MATCH_END) {
	    /*
	     * Anchored at end, Find only place match could occur (leftLen
	     * characters from the end of the word) and see if it does. Note
	     * that because the $ will be left at the end of the lhs, we have
	     * to use strncmp.
	     */
	    cp = word + (wordLen - pattern->leftLen);
	    if ((cp >= word) &&
		(strncmp(cp, pattern->lhs, pattern->leftLen) == 0)) {
		/*
		 * Match found. If we will place characters in the buffer,
		 * add a space before hand as indicated by addSpace, then
		 * stuff in the initial, unmatched part of the word followed
		 * by the right-hand-side.
		 */
		if (((cp - word) + pattern->rightLen) != 0) {
		    if (addSpace && vpstate->varSpace) {
			Buf_AddByte(buf, vpstate->varSpace);
		    }
		    addSpace = TRUE;
		}
		Buf_AddBytes(buf, cp - word, (const Byte *)word);
		Buf_AddBytes(buf, pattern->rightLen,
		    (const Byte *)pattern->rhs);
		pattern->flags |= VAR_SUB_MATCHED;
	    } else {
		/*
		 * Had to match at end and didn't. Copy entire word.
		 */
		goto nosub;
	    }
	} else {
	    /*
	     * Pattern is unanchored: search for the pattern in the word using
	     * String_FindSubstring, copying unmatched portions and the
	     * right-hand-side for each match found, handling non-global
	     * substitutions correctly, etc. When the loop is done, any
	     * remaining part of the word (word and wordLen are adjusted
	     * accordingly through the loop) is copied straight into the
	     * buffer.
	     * addSpace is set FALSE as soon as a space is added to the
	     * buffer.
	     */
	    Boolean done;
	    int origSize;

	    done = FALSE;
	    origSize = Buf_Size(buf);
	    while (!done) {
		cp = Str_FindSubstring(word, pattern->lhs);
		if (cp != NULL) {
		    if (addSpace && (((cp - word) + pattern->rightLen) != 0)){
			Buf_AddByte(buf, vpstate->varSpace);
			addSpace = FALSE;
		    }
		    Buf_AddBytes(buf, cp-word, (const Byte *)word);
		    Buf_AddBytes(buf, pattern->rightLen,
			(const Byte *)pattern->rhs);
		    wordLen -= (cp - word) + pattern->leftLen;
		    word = cp + pattern->leftLen;
		    if (wordLen == 0) {
			done = TRUE;
		    }
		    if ((pattern->flags & VAR_SUB_GLOBAL) == 0) {
			done = TRUE;
		    }
		    pattern->flags |= VAR_SUB_MATCHED;
		} else {
		    done = TRUE;
		}
	    }
	    if (wordLen != 0) {
		if (addSpace && vpstate->varSpace) {
		    Buf_AddByte(buf, vpstate->varSpace);
		}
		Buf_AddBytes(buf, wordLen, (Byte *)word);
	    }
	    /*
	     * If added characters to the buffer, need to add a space
	     * before we add any more. If we didn't add any, just return
	     * the previous value of addSpace.
	     */
	    return ((Buf_Size(buf) != origSize) || addSpace);
	}
	return (addSpace);
    }
 nosub:
    if (addSpace && vpstate->varSpace) {
	Buf_AddByte(buf, vpstate->varSpace);
    }
    Buf_AddBytes(buf, wordLen, (Byte *)word);
    return(TRUE);
}

#ifndef NO_REGEX
/*-
 *-----------------------------------------------------------------------
 * VarREError --
 *	Print the error caused by a regcomp or regexec call.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	An error gets printed.
 *
 *-----------------------------------------------------------------------
 */
static void
VarREError(int err, regex_t *pat, const char *str)
{
    char *errbuf;
    int errlen;

    errlen = regerror(err, pat, 0, 0);
    errbuf = emalloc(errlen);
    regerror(err, pat, errbuf, errlen);
    Error("%s: %s", str, errbuf);
    free(errbuf);
}


/*-
 *-----------------------------------------------------------------------
 * VarRESubstitute --
 *	Perform a regex substitution on the given word, placing the
 *	result in the passed buffer.
 *
 * Results:
 *	TRUE if a space is needed before more characters are added.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarRESubstitute(GNode *ctx __unused, Var_Parse_State *vpstate __unused,
		char *word, Boolean addSpace, Buffer buf,
		ClientData patternp)
{
    VarREPattern *pat;
    int xrv;
    char *wp;
    char *rp;
    int added;
    int flags = 0;

#define MAYBE_ADD_SPACE()		\
	if (addSpace && !added)		\
	    Buf_AddByte(buf, ' ');	\
	added = 1

    added = 0;
    wp = word;
    pat = patternp;

    if ((pat->flags & (VAR_SUB_ONE|VAR_SUB_MATCHED)) ==
	(VAR_SUB_ONE|VAR_SUB_MATCHED))
	xrv = REG_NOMATCH;
    else {
    tryagain:
	xrv = regexec(&pat->re, wp, pat->nsub, pat->matches, flags);
    }

    switch (xrv) {
    case 0:
	pat->flags |= VAR_SUB_MATCHED;
	if (pat->matches[0].rm_so > 0) {
	    MAYBE_ADD_SPACE();
	    Buf_AddBytes(buf, pat->matches[0].rm_so, wp);
	}

	for (rp = pat->replace; *rp; rp++) {
	    if ((*rp == '\\') && ((rp[1] == '&') || (rp[1] == '\\'))) {
		MAYBE_ADD_SPACE();
		Buf_AddByte(buf,rp[1]);
		rp++;
	    }
	    else if ((*rp == '&') ||
		((*rp == '\\') && isdigit((unsigned char)rp[1]))) {
		int n;
		const char *subbuf;
		int sublen;
		char errstr[3];

		if (*rp == '&') {
		    n = 0;
		    errstr[0] = '&';
		    errstr[1] = '\0';
		} else {
		    n = rp[1] - '0';
		    errstr[0] = '\\';
		    errstr[1] = rp[1];
		    errstr[2] = '\0';
		    rp++;
		}

		if (n > pat->nsub) {
		    Error("No subexpression %s", &errstr[0]);
		    subbuf = "";
		    sublen = 0;
		} else if ((pat->matches[n].rm_so == -1) &&
			   (pat->matches[n].rm_eo == -1)) {
		    Error("No match for subexpression %s", &errstr[0]);
		    subbuf = "";
		    sublen = 0;
	        } else {
		    subbuf = wp + pat->matches[n].rm_so;
		    sublen = pat->matches[n].rm_eo - pat->matches[n].rm_so;
		}

		if (sublen > 0) {
		    MAYBE_ADD_SPACE();
		    Buf_AddBytes(buf, sublen, subbuf);
		}
	    } else {
		MAYBE_ADD_SPACE();
		Buf_AddByte(buf, *rp);
	    }
	}
	wp += pat->matches[0].rm_eo;
	if (pat->flags & VAR_SUB_GLOBAL) {
	    flags |= REG_NOTBOL;
	    if (pat->matches[0].rm_so == 0 && pat->matches[0].rm_eo == 0) {
		MAYBE_ADD_SPACE();
		Buf_AddByte(buf, *wp);
		wp++;

	    }
	    if (*wp)
		goto tryagain;
	}
	if (*wp) {
	    MAYBE_ADD_SPACE();
	    Buf_AddBytes(buf, strlen(wp), wp);
	}
	break;
    default:
	VarREError(xrv, &pat->re, "Unexpected regex error");
       /* fall through */
    case REG_NOMATCH:
	if (*wp) {
	    MAYBE_ADD_SPACE();
	    Buf_AddBytes(buf,strlen(wp),wp);
	}
	break;
    }
    return(addSpace||added);
}
#endif



/*-
 *-----------------------------------------------------------------------
 * VarLoopExpand --
 *	Implements the :@<temp>@<string>@ modifier of ODE make.
 *	We set the temp variable named in pattern.lhs to word and expand
 *	pattern.rhs storing the result in the passed buffer.
 *
 * Input:
 *	word		Word to modify
 *	addSpace	True if space should be added before
 *			other characters
 *	buf		Buffer for result
 *	pattern		Datafor substitution
 *
 * Results:
 *	TRUE if a space is needed before more characters are added.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static Boolean
VarLoopExpand(GNode *ctx __unused, Var_Parse_State *vpstate __unused,
	      char *word, Boolean addSpace, Buffer buf,
	      ClientData loopp)
{
    VarLoop_t	*loop = (VarLoop_t *)loopp;
    char *s;
    int slen;

    if (word && *word) {
        Var_Set(loop->tvar, word, loop->ctxt, VAR_NO_EXPORT);
        s = Var_Subst(NULL, loop->str, loop->ctxt, loop->err);
        if (s != NULL && *s != '\0') {
            if (addSpace && *s != '\n')
                Buf_AddByte(buf, ' ');
            Buf_AddBytes(buf, (slen = strlen(s)), (Byte *)s);
            addSpace = (slen > 0 && s[slen - 1] != '\n');
            free(s);
        }
    }
    return addSpace;
}


/*-
 *-----------------------------------------------------------------------
 * VarSelectWords --
 *	Implements the :[start..end] modifier.
 *	This is a special case of VarModify since we want to be able
 *	to scan the list backwards if start > end.
 *
 * Input:
 *	str		String whose words should be trimmed
 *	seldata		words to select
 *
 * Results:
 *	A string of all the words selected.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarSelectWords(GNode *ctx __unused, Var_Parse_State *vpstate,
	       const char *str, VarSelectWords_t *seldata)
{
    Buffer  	  buf;	    	    /* Buffer for the new string */
    Boolean 	  addSpace; 	    /* TRUE if need to add a space to the
				     * buffer before adding the trimmed
				     * word */
    char **av;			    /* word list */
    char *as;			    /* word list memory */
    int ac, i;
    int start, end, step;
    
    buf = Buf_Init(0);
    addSpace = FALSE;

    if (vpstate->oneBigWord) {
	/* fake what brk_string() would do if there were only one word */
	ac = 1;
    	av = emalloc((ac + 1) * sizeof(char *));
	as = strdup(str);
	av[0] = as;
	av[1] = NULL;
    } else {
	av = brk_string(str, &ac, FALSE, &as);
    }

    /*
     * Now sanitize seldata.
     * If seldata->start or seldata->end are negative, convert them to
     * the positive equivalents (-1 gets converted to argc, -2 gets
     * converted to (argc-1), etc.).
     */
    if (seldata->start < 0)
	seldata->start = ac + seldata->start + 1;
    if (seldata->end < 0)
	seldata->end = ac + seldata->end + 1;

    /*
     * We avoid scanning more of the list than we need to.
     */
    if (seldata->start > seldata->end) {
	start = MIN(ac, seldata->start) - 1;
	end = MAX(0, seldata->end - 1);
	step = -1;
    } else {
	start = MAX(0, seldata->start - 1);
	end = MIN(ac, seldata->end);
	step = 1;
    }

    for (i = start;
	 (step < 0 && i >= end) || (step > 0 && i < end);
	 i += step) {
	if (av[i] && *av[i]) {
	    if (addSpace && vpstate->varSpace) {
		Buf_AddByte(buf, vpstate->varSpace);
	    }
	    Buf_AddBytes(buf, strlen(av[i]), (Byte *)av[i]);
	    addSpace = TRUE;
	}
    }

    free(as);
    free(av);

    Buf_AddByte(buf, '\0');
    as = (char *)Buf_GetAll(buf, NULL);
    Buf_Destroy(buf, FALSE);
    return (as);
}

/*-
 *-----------------------------------------------------------------------
 * VarModify --
 *	Modify each of the words of the passed string using the given
 *	function. Used to implement all modifiers.
 *
 * Input:
 *	str		String whose words should be trimmed
 *	modProc		Function to use to modify them
 *	datum		Datum to pass it
 *
 * Results:
 *	A string of all the words modified appropriately.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarModify(GNode *ctx, Var_Parse_State *vpstate,
    const char *str,
    Boolean (*modProc)(GNode *, Var_Parse_State *, char *,
		       Boolean, Buffer, ClientData),
    ClientData datum)
{
    Buffer  	  buf;	    	    /* Buffer for the new string */
    Boolean 	  addSpace; 	    /* TRUE if need to add a space to the
				     * buffer before adding the trimmed
				     * word */
    char **av;			    /* word list */
    char *as;			    /* word list memory */
    int ac, i;

    buf = Buf_Init(0);
    addSpace = FALSE;

    if (vpstate->oneBigWord) {
	/* fake what brk_string() would do if there were only one word */
	ac = 1;
    	av = emalloc((ac + 1) * sizeof(char *));
	as = strdup(str);
	av[0] = as;
	av[1] = NULL;
    } else {
	av = brk_string(str, &ac, FALSE, &as);
    }

    for (i = 0; i < ac; i++) {
	addSpace = (*modProc)(ctx, vpstate, av[i], addSpace, buf, datum);
    }

    free(as);
    free(av);

    Buf_AddByte(buf, '\0');
    as = (char *)Buf_GetAll(buf, NULL);
    Buf_Destroy(buf, FALSE);
    return (as);
}


static int
VarWordCompare(const void *a, const void *b)
{
	int r = strcmp(*(const char * const *)a, *(const char * const *)b);
	return r;
}

/*-
 *-----------------------------------------------------------------------
 * VarOrder --
 *	Order the words in the string.
 *
 * Input:
 *	str		String whose words should be sorted.
 *	otype		How to order: s - sort, x - random.
 *
 * Results:
 *	A string containing the words ordered.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarOrder(const char *str, const char otype)
{
    Buffer  	  buf;	    	    /* Buffer for the new string */
    char **av;			    /* word list [first word does not count] */
    char *as;			    /* word list memory */
    int ac, i;

    buf = Buf_Init(0);

    av = brk_string(str, &ac, FALSE, &as);

    if (ac > 0)
	switch (otype) {
	case 's':	/* sort alphabetically */
	    qsort(av, ac, sizeof(char *), VarWordCompare);
	    break;
	case 'x':	/* randomize */
	{
	    int rndidx;
	    char *t;

	    /*
	     * We will use [ac..2] range for mod factors. This will produce
	     * random numbers in [(ac-1)..0] interval, and minimal
	     * reasonable value for mod factor is 2 (the mod 1 will produce
	     * 0 with probability 1).
	     */
	    for (i = ac-1; i > 0; i--) {
		rndidx = random() % (i + 1);
		if (i != rndidx) {
		    t = av[i];
		    av[i] = av[rndidx];
		    av[rndidx] = t;
		}
	    }
	}
	} /* end of switch */

    for (i = 0; i < ac; i++) {
	Buf_AddBytes(buf, strlen(av[i]), (Byte *)av[i]);
	if (i != ac - 1)
	    Buf_AddByte(buf, ' ');
    }

    free(as);
    free(av);

    Buf_AddByte(buf, '\0');
    as = (char *)Buf_GetAll(buf, NULL);
    Buf_Destroy(buf, FALSE);
    return (as);
}


/*-
 *-----------------------------------------------------------------------
 * VarUniq --
 *	Remove adjacent duplicate words.
 *
 * Input:
 *	str		String whose words should be sorted
 *
 * Results:
 *	A string containing the resulting words.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarUniq(const char *str)
{
    Buffer	  buf;	    	    /* Buffer for new string */
    char 	**av;		    /* List of words to affect */
    char 	 *as;		    /* Word list memory */
    int 	  ac, i, j;

    buf = Buf_Init(0);
    av = brk_string(str, &ac, FALSE, &as);

    if (ac > 1) {
	for (j = 0, i = 1; i < ac; i++)
	    if (strcmp(av[i], av[j]) != 0 && (++j != i))
		av[j] = av[i];
	ac = j + 1;
    }

    for (i = 0; i < ac; i++) {
	Buf_AddBytes(buf, strlen(av[i]), (Byte *)av[i]);
	if (i != ac - 1)
	    Buf_AddByte(buf, ' ');
    }

    free(as);
    free(av);

    Buf_AddByte(buf, '\0');
    as = (char *)Buf_GetAll(buf, NULL);
    Buf_Destroy(buf, FALSE);
    return as;
}


/*-
 *-----------------------------------------------------------------------
 * VarGetPattern --
 *	Pass through the tstr looking for 1) escaped delimiters,
 *	'$'s and backslashes (place the escaped character in
 *	uninterpreted) and 2) unescaped $'s that aren't before
 *	the delimiter (expand the variable substitution unless flags
 *	has VAR_NOSUBST set).
 *	Return the expanded string or NULL if the delimiter was missing
 *	If pattern is specified, handle escaped ampersands, and replace
 *	unescaped ampersands with the lhs of the pattern.
 *
 * Results:
 *	A string of all the words modified appropriately.
 *	If length is specified, return the string length of the buffer
 *	If flags is specified and the last character of the pattern is a
 *	$ set the VAR_MATCH_END bit of flags.
 *
 * Side Effects:
 *	None.
 *-----------------------------------------------------------------------
 */
static char *
VarGetPattern(GNode *ctxt, Var_Parse_State *vpstate __unused,
	      int err, const char **tstr, int delim, int *flags,
	      int *length, VarPattern *pattern)
{
    const char *cp;
    Buffer buf = Buf_Init(0);
    int junk;
    if (length == NULL)
	length = &junk;

#define IS_A_MATCH(cp, delim) \
    ((cp[0] == '\\') && ((cp[1] == delim) ||  \
     (cp[1] == '\\') || (cp[1] == '$') || (pattern && (cp[1] == '&'))))

    /*
     * Skim through until the matching delimiter is found;
     * pick up variable substitutions on the way. Also allow
     * backslashes to quote the delimiter, $, and \, but don't
     * touch other backslashes.
     */
    for (cp = *tstr; *cp && (*cp != delim); cp++) {
	if (IS_A_MATCH(cp, delim)) {
	    Buf_AddByte(buf, (Byte)cp[1]);
	    cp++;
	} else if (*cp == '$') {
	    if (cp[1] == delim) {
		if (flags == NULL)
		    Buf_AddByte(buf, (Byte)*cp);
		else
		    /*
		     * Unescaped $ at end of pattern => anchor
		     * pattern at end.
		     */
		    *flags |= VAR_MATCH_END;
	    } else {
		if (flags == NULL || (*flags & VAR_NOSUBST) == 0) {
		    char   *cp2;
		    int     len;
		    Boolean freeIt;

		    /*
		     * If unescaped dollar sign not before the
		     * delimiter, assume it's a variable
		     * substitution and recurse.
		     */
		    cp2 = Var_Parse(cp, ctxt, err, &len, &freeIt);
		    Buf_AddBytes(buf, strlen(cp2), (Byte *)cp2);
		    if (freeIt)
			free(cp2);
		    cp += len - 1;
		} else {
		    const char *cp2 = &cp[1];

		    if (*cp2 == PROPEN || *cp2 == BROPEN) {
			/*
			 * Find the end of this variable reference
			 * and suck it in without further ado.
			 * It will be interperated later.
			 */
			int have = *cp2;
			int want = (*cp2 == PROPEN) ? PRCLOSE : BRCLOSE;
			int depth = 1;

			for (++cp2; *cp2 != '\0' && depth > 0; ++cp2) {
			    if (cp2[-1] != '\\') {
				if (*cp2 == have)
				    ++depth;
				if (*cp2 == want)
				    --depth;
			    }
			}
			Buf_AddBytes(buf, cp2 - cp, (const Byte *)cp);
			cp = --cp2;
		    } else
			Buf_AddByte(buf, (Byte)*cp);
		}
	    }
	}
	else if (pattern && *cp == '&')
	    Buf_AddBytes(buf, pattern->leftLen, (const Byte *)pattern->lhs);
	else
	    Buf_AddByte(buf, (Byte)*cp);
    }

    Buf_AddByte(buf, (Byte)'\0');

    if (*cp != delim) {
	*tstr = cp;
	*length = 0;
	return NULL;
    }
    else {
	char *rstr;
	*tstr = ++cp;
	rstr = (char *)Buf_GetAll(buf, length);
	*length -= 1;	/* Don't count the NULL */
	Buf_Destroy(buf, FALSE);
	return rstr;
    }
}

/*-
 *-----------------------------------------------------------------------
 * VarQuote --
 *	Quote shell meta-characters in the string
 *
 * Results:
 *	The quoted string
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarQuote(char *str)
{

    Buffer  	  buf;
    /* This should cover most shells :-( */
    static char meta[] = "\n \t'`\";&<>()|*?{}[]\\$!#^~";

    buf = Buf_Init(MAKE_BSIZE);
    for (; *str; str++) {
	if (strchr(meta, *str) != NULL)
	    Buf_AddByte(buf, (Byte)'\\');
	Buf_AddByte(buf, (Byte)*str);
    }
    Buf_AddByte(buf, (Byte)'\0');
    str = (char *)Buf_GetAll(buf, NULL);
    Buf_Destroy(buf, FALSE);
    return str;
}

/*-
 *-----------------------------------------------------------------------
 * VarChangeCase --
 *      Change the string to all uppercase or all lowercase
 *
 * Input:
 *	str		String to modify
 *	upper		TRUE -> uppercase, else lowercase
 *
 * Results:
 *      The string with case changed
 *
 * Side Effects:
 *      None.
 *
 *-----------------------------------------------------------------------
 */
static char *
VarChangeCase(char *str, int upper)
{
   Buffer         buf;
   int            (*modProc)(int);

   modProc = (upper ? toupper : tolower);
   buf = Buf_Init(MAKE_BSIZE);
   for (; *str ; str++) {
       Buf_AddByte(buf, (Byte)modProc(*str));
   }
   Buf_AddByte(buf, (Byte)'\0');
   str = (char *)Buf_GetAll(buf, NULL);
   Buf_Destroy(buf, FALSE);
   return str;
}

/*-
 *-----------------------------------------------------------------------
 * Var_Parse --
 *	Given the start of a variable invocation, extract the variable
 *	name and find its value, then modify it according to the
 *	specification.
 *
 * Input:
 *	str		The string to parse
 *	ctxt		The context for the variable
 *	err		TRUE if undefined variables are an error
 *	lengthPtr	OUT: The length of the specification
 *	freePtr		OUT: TRUE if caller should free result
 *
 * Results:
 *	The (possibly-modified) value of the variable or var_Error if the
 *	specification is invalid. The length of the specification is
 *	placed in *lengthPtr (for invalid specifications, this is just
 *	2...?).
 *	A Boolean in *freePtr telling whether the returned string should
 *	be freed by the caller.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
char *
Var_Parse(const char *str, GNode *ctxt, Boolean err, int *lengthPtr,
	  Boolean *freePtr)
{
    const char	   *tstr;    	/* Pointer into str */
    Var	    	   *v;	    	/* Variable in invocation */
    const char     *cp;    	/* Secondary pointer into str (place marker
				 * for tstr) */
    Boolean 	    haveModifier;/* TRUE if have modifiers for the variable */
    char	    endc;    	/* Ending character when variable in parens
				 * or braces */
    char	    startc=0;	/* Starting character when variable in parens
				 * or braces */
    int             cnt;	/* Used to count brace pairs when variable in
				 * in parens or braces */
    int		    vlen;	/* Length of variable name */
    const char 	   *start;
    char	    delim;
    char	   *nstr;
    Boolean 	    dynamic;	/* TRUE if the variable is local and we're
				 * expanding it in a non-local context. This
				 * is done to support dynamic sources. The
				 * result is just the invocation, unaltered */
    Var_Parse_State parsestate; /* Flags passed to helper functions */

    *freePtr = FALSE;
    dynamic = FALSE;
    start = str;
    parsestate.oneBigWord = FALSE;
    parsestate.varSpace = ' ';	/* word separator */

    if (str[1] != PROPEN && str[1] != BROPEN) {
	/*
	 * If it's not bounded by braces of some sort, life is much simpler.
	 * We just need to check for the first character and return the
	 * value if it exists.
	 */
	char	  name[2];

	name[0] = str[1];
	name[1] = '\0';

	v = VarFind(name, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
	if (v == (Var *)NIL) {
	    *lengthPtr = 2;

	    if ((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)) {
		/*
		 * If substituting a local variable in a non-local context,
		 * assume it's for dynamic source stuff. We have to handle
		 * this specially and return the longhand for the variable
		 * with the dollar sign escaped so it makes it back to the
		 * caller. Only four of the local variables are treated
		 * specially as they are the only four that will be set
		 * when dynamic sources are expanded.
		 */
		switch (str[1]) {
		    case '@':
			return UNCONST("$(.TARGET)");
		    case '%':
			return UNCONST("$(.ARCHIVE)");
		    case '*':
			return UNCONST("$(.PREFIX)");
		    case '!':
			return UNCONST("$(.MEMBER)");
		}
	    }
	    /*
	     * Error
	     */
	    return (err ? var_Error : varNoError);
	} else {
	    haveModifier = FALSE;
	    tstr = &str[1];
	    endc = str[1];
	}
    } else if (str[1] == '\0') {
	*lengthPtr = 1;
	return (err ? var_Error : varNoError);
    } else { 
	Buffer buf;	/* Holds the variable name */

	startc = str[1];
	endc = startc == PROPEN ? PRCLOSE : BRCLOSE;
	buf = Buf_Init(MAKE_BSIZE);

	/*
	 * Skip to the end character or a colon, whichever comes first.
	 */
	for (tstr = str + 2;
	     *tstr != '\0' && *tstr != endc && *tstr != ':';
	     tstr++)
	{
	    /*
	     * A variable inside a variable, expand
	     */
	    if (*tstr == '$') {
		int rlen;
		Boolean rfree;
		char *rval = Var_Parse(tstr, ctxt, err, &rlen, &rfree);
		if (rval != NULL) {
		    Buf_AddBytes(buf, strlen(rval), (Byte *)rval);
		    if (rfree)
			free(rval);
		}
		tstr += rlen - 1;
	    }
	    else
		Buf_AddByte(buf, (Byte)*tstr);
	}
	if (*tstr == ':') {
	    haveModifier = TRUE;
	} else if (*tstr != '\0') {
	    haveModifier = FALSE;
	} else {
	    /*
	     * If we never did find the end character, return NULL
	     * right now, setting the length to be the distance to
	     * the end of the string, since that's what make does.
	     */
	    *lengthPtr = tstr - str;
	    return (var_Error);
	}
	*WR(tstr) = '\0';
	Buf_AddByte(buf, (Byte)'\0');
	str = Buf_GetAll(buf, NULL);
	vlen = strlen(str);

	v = VarFind(str, ctxt, FIND_ENV | FIND_GLOBAL | FIND_CMD);
	if ((v == (Var *)NIL) && (ctxt != VAR_CMD) && (ctxt != VAR_GLOBAL) &&
	    (vlen == 2) && (str[1] == 'F' || str[1] == 'D'))
	{
	    /*
	     * Check for bogus D and F forms of local variables since we're
	     * in a local context and the name is the right length.
	     */
	    switch(*str) {
		case '@':
		case '%':
		case '*':
		case '!':
		case '>':
		case '<':
		{
		    char    vname[2];
		    char    *val;

		    /*
		     * Well, it's local -- go look for it.
		     */
		    vname[0] = *str;
		    vname[1] = '\0';
		    v = VarFind(vname, ctxt, 0);

		    if (v != (Var *)NIL) {
			/*
			 * No need for nested expansion or anything, as we're
			 * the only one who sets these things and we sure don't
			 * but nested invocations in them...
			 */
			val = (char *)Buf_GetAll(v->val, NULL);

			if (str[1] == 'D') {
			    val = VarModify(ctxt, &parsestate, val, VarHead,
					    (ClientData)0);
			} else {
			    val = VarModify(ctxt, &parsestate, val, VarTail,
					    (ClientData)0);
			}
			/*
			 * Resulting string is dynamically allocated, so
			 * tell caller to free it.
			 */
			*freePtr = TRUE;
			*lengthPtr = tstr-start+1;
			*WR(tstr) = endc;
			Buf_Destroy(buf, TRUE);
			return(val);
		    }
		    break;
		}
	    }
	}

	if (v == (Var *)NIL) {
	    if (((vlen == 1) ||
		 (((vlen == 2) && (str[1] == 'F' ||
					 str[1] == 'D')))) &&
		((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)))
	    {
		/*
		 * If substituting a local variable in a non-local context,
		 * assume it's for dynamic source stuff. We have to handle
		 * this specially and return the longhand for the variable
		 * with the dollar sign escaped so it makes it back to the
		 * caller. Only four of the local variables are treated
		 * specially as they are the only four that will be set
		 * when dynamic sources are expanded.
		 */
		switch (*str) {
		    case '@':
		    case '%':
		    case '*':
		    case '!':
			dynamic = TRUE;
			break;
		}
	    } else if ((vlen > 2) && (*str == '.') &&
		       isupper((unsigned char) str[1]) &&
		       ((ctxt == VAR_CMD) || (ctxt == VAR_GLOBAL)))
	    {
		int	len;

		len = vlen - 1;
		if ((strncmp(str, ".TARGET", len) == 0) ||
		    (strncmp(str, ".ARCHIVE", len) == 0) ||
		    (strncmp(str, ".PREFIX", len) == 0) ||
		    (strncmp(str, ".MEMBER", len) == 0))
		{
		    dynamic = TRUE;
		}
	    }

	    if (!haveModifier) {
		/*
		 * No modifiers -- have specification length so we can return
		 * now.
		 */
		*lengthPtr = tstr - start + 1;
		*WR(tstr) = endc;
		if (dynamic) {
		    char *pstr = emalloc(*lengthPtr + 1);
		    strncpy(pstr, start, *lengthPtr);
		    pstr[*lengthPtr] = '\0';
		    *freePtr = TRUE;
		    Buf_Destroy(buf, TRUE);
		    return(pstr);
		} else {
		    Buf_Destroy(buf, TRUE);
		    return (err ? var_Error : varNoError);
		}
	    } else {
		/*
		 * Still need to get to the end of the variable specification,
		 * so kludge up a Var structure for the modifications
		 */
		v = emalloc(sizeof(Var));
		v->name = UNCONST(str);
		v->val = Buf_Init(1);
		v->flags = VAR_JUNK;
		Buf_Destroy(buf, FALSE);
	    }
	} else
	    Buf_Destroy(buf, TRUE);
    }


    if (v->flags & VAR_IN_USE) {
	Fatal("Variable %s is recursive.", v->name);
	/*NOTREACHED*/
    } else {
	v->flags |= VAR_IN_USE;
    }
    /*
     * Before doing any modification, we have to make sure the value
     * has been fully expanded. If it looks like recursion might be
     * necessary (there's a dollar sign somewhere in the variable's value)
     * we just call Var_Subst to do any other substitutions that are
     * necessary. Note that the value returned by Var_Subst will have
     * been dynamically-allocated, so it will need freeing when we
     * return.
     */
    nstr = (char *)Buf_GetAll(v->val, NULL);
    if (strchr(nstr, '$') != NULL) {
	nstr = Var_Subst(NULL, nstr, ctxt, err);
	*freePtr = TRUE;
    }

    v->flags &= ~VAR_IN_USE;

    /*
     * Now we need to apply any modifiers the user wants applied.
     * These are:
     *  	  :M<pattern>	words which match the given <pattern>.
     *  	  	    	<pattern> is of the standard file
     *  	  	    	wildcarding form.
     *  	  :N<pattern>	words which do not match the given <pattern>.
     *  	  :S<d><pat1><d><pat2><d>[1gW]
     *  	  	    	Substitute <pat2> for <pat1> in the value
     *  	  :C<d><pat1><d><pat2><d>[1gW]
     *  	  	    	Substitute <pat2> for regex <pat1> in the value
     *  	  :H	    	Substitute the head of each word
     *  	  :T	    	Substitute the tail of each word
     *  	  :E	    	Substitute the extension (minus '.') of
     *  	  	    	each word
     *  	  :R	    	Substitute the root of each word
     *  	  	    	(pathname minus the suffix).
     *		  :O		("Order") Alphabeticaly sort words in variable.
     *		  :Ox		("intermiX") Randomize words in variable.
     *		  :u		("uniq") Remove adjacent duplicate words.
     *		  :tu		Converts the variable contents to uppercase.
     *		  :tl		Converts the variable contents to lowercase.
     *		  :ts[c]	Sets varSpace - the char used to
     *				separate words to 'c'. If 'c' is
     *				omitted then no separation is used.
     *		  :tW		Treat the variable contents as a single
     *				word, even if it contains spaces.
     *				(Mnemonic: one big 'W'ord.)
     *		  :tw		Treat the variable contents as multiple
     *				space-separated words.
     *				(Mnemonic: many small 'w'ords.)
     *		  :[index]	Select a single word from the value.
     *		  :[start..end]	Select multiple words from the value.
     *		  :[*] or :[0]	Select the entire value, as a single
     *				word.  Equivalent to :tW.
     *		  :[@]		Select the entire value, as multiple
     *				words.	Undoes the effect of :[*].
     *				Equivalent to :tw.
     *		  :[#]		Returns the number of words in the value.
     *
     *		  :?<true-value>:<false-value>
     *				If the variable evaluates to true, return
     *				true value, else return the second value.
     *	    	  :lhs=rhs  	Like :S, but the rhs goes to the end of
     *	    	    	    	the invocation.
     *		  :sh		Treat the current value as a command
     *				to be run, new value is its output.
     * The following added so we can handle ODE makefiles.
     *		  :@<tmpvar>@<newval>@
     *				Assign a temporary local variable <tmpvar>
     *				to the current value of each word in turn
     *				and replace each word with the result of
     *				evaluating <newval>
     *		  :D<newval>	Use <newval> as value if variable defined
     *		  :U<newval>	Use <newval> as value if variable undefined
     *		  :L		Use the name of the variable as the value.
     *		  :P		Use the path of the node that has the same
     *				name as the variable as the value.  This
     *				basically includes an implied :L so that
     *				the common method of refering to the path
     *				of your dependent 'x' in a rule is to use
     *				the form '${x:P}'.
     *		  :!<cmd>!	Run cmd much the same as :sh run's the
     *				current value of the variable.
     * The ::= modifiers, actually assign a value to the variable.
     * Their main purpose is in supporting modifiers of .for loop
     * iterators and other obscure uses.  They always expand to
     * nothing.  In a target rule that would otherwise expand to an
     * empty line they can be preceded with @: to keep make happy.
     * Eg.
     * 
     * foo:	.USE
     * .for i in ${.TARGET} ${.TARGET:R}.gz
     * 		@: ${t::=$i}
     *		@echo blah ${t:T}
     * .endfor
     * 
     *		  ::=<str>	Assigns <str> as the new value of variable.
     *		  ::?=<str>	Assigns <str> as value of variable if
     *				it was not already set.
     *		  ::+=<str>	Appends <str> to variable.
     *		  ::!=<cmd>	Assigns output of <cmd> as the new value of
     *				variable.
     */
    if ((nstr != NULL) && haveModifier) {
	/*
	 * Skip initial colon while putting it back.
	 */
	*WR(tstr) = ':';
	tstr++;
	delim = '\0';

	while (*tstr && *tstr != endc) {
	    char	*newStr;    /* New value to return */
	    char	termc;	    /* Character which terminated scan */

	    if (DEBUG(VAR)) {
		printf("Applying :%c to \"%s\"\n", *tstr, nstr);
	    }
	    newStr = var_Error;
	    switch (*tstr) {
	        case ':':
		{
		if (tstr[1] == '=' ||
		    (tstr[2] == '=' &&
		     (tstr[1] == '!' || tstr[1] == '+' || tstr[1] == '?'))) {
		    /*
		     * "::=", "::!=", "::+=", or "::?="
		     */
		    GNode *v_ctxt;		/* context where v belongs */
		    const char *emsg;
		    char *sv_name;
		    VarPattern	pattern;
		    int	how;

		    v_ctxt = ctxt;
		    sv_name = NULL;
		    ++tstr;
		    if (v->flags & VAR_JUNK) {
			/*
			 * We need to strdup() it incase
			 * VarGetPattern() recurses.
			 */
			sv_name = v->name;
			v->name = strdup(v->name);
		    } else if (ctxt != VAR_GLOBAL) {
			if (VarFind(v->name, ctxt, 0) == (Var *)NIL)
			    v_ctxt = VAR_GLOBAL;
		    }
			
		    switch ((how = *tstr)) {
		    case '+':
		    case '?':
		    case '!':
			cp = &tstr[2];
			break;
		    default:
			cp = ++tstr;
			break;
		    }
		    delim = BRCLOSE;
		    pattern.flags = 0;

		    pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.rightLen,
						     NULL);
		    if (v->flags & VAR_JUNK) {
			/* restore original name */
			free(v->name);
			v->name = sv_name;
		    }
		    if (pattern.rhs == NULL)
			goto cleanup;

		    termc = *--cp;
		    delim = '\0';

		    switch (how) {
		    case '+':
			Var_Append(v->name, pattern.rhs, v_ctxt);
			break;
		    case '!':
			newStr = Cmd_Exec(pattern.rhs, &emsg);
			if (emsg)
			    Error(emsg, nstr);
			else
			   Var_Set(v->name, newStr,  v_ctxt, 0);
			if (newStr)
			    free(newStr);
			break;
		    case '?':
			if ((v->flags & VAR_JUNK) == 0)
			    break;
			/* FALLTHROUGH */
		    default:
			Var_Set(v->name, pattern.rhs, v_ctxt, 0);
			break;
		    }
		    free(UNCONST(pattern.rhs));
		    newStr = var_Error;
		    break;
		}
		goto default_case; /* "::<unrecognised>" */
		}
	        case '@':
		{
		    VarLoop_t	loop;
		    int flags = VAR_NOSUBST;

		    cp = ++tstr;
		    delim = '@';
		    if ((loop.tvar = VarGetPattern(ctxt, &parsestate, err,
						   &cp, delim,
						   &flags, &loop.tvarLen,
						   NULL)) == NULL)
			goto cleanup;

		    if ((loop.str = VarGetPattern(ctxt, &parsestate, err,
						  &cp, delim,
						  &flags, &loop.strLen,
						  NULL)) == NULL)
			goto cleanup;

		    termc = *cp;
		    delim = '\0';

		    loop.err = err;
		    loop.ctxt = ctxt;
		    newStr = VarModify(ctxt, &parsestate, nstr, VarLoopExpand,
				       (ClientData)&loop);
		    free(loop.tvar);
		    free(loop.str);
		    break;
		}
	        case 'D':
	        case 'U':
		{
		    Buffer  buf;    	/* Buffer for patterns */
		    int	    wantit;	/* want data in buffer */

		    /*
		     * Pass through tstr looking for 1) escaped delimiters,
		     * '$'s and backslashes (place the escaped character in
		     * uninterpreted) and 2) unescaped $'s that aren't before
		     * the delimiter (expand the variable substitution).
		     * The result is left in the Buffer buf.
		     */
		    buf = Buf_Init(0);
		    for (cp = tstr + 1;
			 *cp != endc && *cp != ':' && *cp != '\0';
			 cp++) {
			if ((*cp == '\\') &&
			    ((cp[1] == ':') ||
			     (cp[1] == '$') ||
			     (cp[1] == endc) ||
			     (cp[1] == '\\')))
			{
			    Buf_AddByte(buf, (Byte)cp[1]);
			    cp++;
			} else if (*cp == '$') {
			    /*
			     * If unescaped dollar sign, assume it's a
			     * variable substitution and recurse.
			     */
			    char    *cp2;
			    int	    len;
			    Boolean freeIt;

			    cp2 = Var_Parse(cp, ctxt, err, &len, &freeIt);
			    Buf_AddBytes(buf, strlen(cp2), (Byte *)cp2);
			    if (freeIt)
				free(cp2);
			    cp += len - 1;
			} else {
			    Buf_AddByte(buf, (Byte)*cp);
			}
		    }
		    Buf_AddByte(buf, (Byte)'\0');

		    termc = *cp;

		    if (*tstr == 'U')
			wantit = ((v->flags & VAR_JUNK) != 0);
		    else
			wantit = ((v->flags & VAR_JUNK) == 0);
		    if ((v->flags & VAR_JUNK) != 0)
			v->flags |= VAR_KEEP;
		    if (wantit) {
			newStr = (char *)Buf_GetAll(buf, NULL);
			Buf_Destroy(buf, FALSE);
		    } else {
			newStr = nstr;
			Buf_Destroy(buf, TRUE);
		    }
		    break;
		}
	        case 'L':
		{
		    if ((v->flags & VAR_JUNK) != 0)
			v->flags |= VAR_KEEP;
		    newStr = strdup(v->name);
		    cp = ++tstr;
		    termc = *tstr;
		    break;
		}
	        case 'P':
		{
		    GNode *gn;
		    
		    if ((v->flags & VAR_JUNK) != 0)
			v->flags |= VAR_KEEP;
		    gn = Targ_FindNode(v->name, TARG_NOCREATE);
		    if (gn == NILGNODE || gn->path == NULL)
			newStr = strdup(v->name);
		    else
			newStr = strdup(gn->path);
		    cp = ++tstr;
		    termc = *tstr;
		    break;
		}
	        case '!':
		{
		    const char *emsg;
		    VarPattern 	    pattern;
		    pattern.flags = 0;

		    delim = '!';

		    cp = ++tstr;
		    if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim,
						     NULL, &pattern.rightLen,
						     NULL)) == NULL)
			goto cleanup;
		    newStr = Cmd_Exec(pattern.rhs, &emsg);
		    free(UNCONST(pattern.rhs));
		    if (emsg)
			Error(emsg, nstr);
		    termc = *cp;
		    delim = '\0';
		    if (v->flags & VAR_JUNK) {
			v->flags |= VAR_KEEP;
		    }
		    break;
		}
		case '[':
		{
		    /*
		     * Look for the closing ']', recursively
		     * expanding any embedded variables.
		     *
		     * estr is a pointer to the expanded result,
		     * which we must free().
		     */
		    char *estr;
		    
		    cp = tstr+1; /* point to char after '[' */
		    delim = ']'; /* look for closing ']' */
		    estr = VarGetPattern(ctxt, &parsestate,
					 err, &cp, delim,
					 NULL, NULL, NULL);
		    if (estr == NULL)
			goto cleanup; /* report missing ']' */
		    /* now cp points just after the closing ']' */
		    delim = '\0';
		    if (cp[0] != ':' && cp[0] != endc) {
			/* Found junk after ']' */
			free(estr);
			goto bad_modifier;
		    }
		    if (estr[0] == '\0') {
			/* Found empty square brackets in ":[]". */
			free(estr);
			goto bad_modifier;
		    } else if (estr[0] == '#' && estr[1] == '\0') {
			/* Found ":[#]" */

			/*
			 * We will need enough space for the decimal
			 * representation of an int.  We calculate the
			 * space needed for the octal representation,
			 * and add enough slop to cope with a '-' sign
			 * (which should never be needed) and a '\0'
			 * string terminator.
			 */
			 int newStrSize =
				 (sizeof(int) * CHAR_BIT + 2) / 3 + 2;

			newStr = emalloc(newStrSize);
			if (parsestate.oneBigWord) {
				strncpy(newStr, "1", newStrSize);
			} else {
			    /* XXX: brk_string() is a rather expensive
			     * way of counting words. */
			    char **av;
			    char *as;
			    int ac;

			    av = brk_string(nstr, &ac, FALSE, &as);
			    snprintf(newStr, newStrSize,  "%d", ac);
			    free(as);
			    free(av);
			}
			termc = *cp;
			free(estr);
			break;
		    } else if (estr[0] == '*' && estr[1] == '\0') {
			/* Found ":[*]" */
			parsestate.oneBigWord = TRUE;
			newStr = nstr;
			termc = *cp;
			free(estr);
			break;
		    } else if (estr[0] == '@' && estr[1] == '\0') {
			/* Found ":[@]" */
			parsestate.oneBigWord = FALSE;
			newStr = nstr;
			termc = *cp;
			free(estr);
			break;
		    } else {
			/*
			 * We expect estr to contain a single
			 * integer for :[N], or two integers
			 * separated by ".." for :[start..end].
			 */
			char *ep;

			VarSelectWords_t seldata = { 0, 0 };

			seldata.start = strtol(estr, &ep, 0);
			if (ep == estr) {
			    /* Found junk instead of a number */
			    free(estr);
			    goto bad_modifier;
			} else if (ep[0] == '\0') {
			    /* Found only one integer in :[N] */
			    seldata.end = seldata.start;
			} else if (ep[0] == '.' && ep[1] == '.' &&
				   ep[2] != '\0') {
			    /* Expecting another integer after ".." */
			    ep += 2;
			    seldata.end = strtol(ep, &ep, 0);
			    if (ep[0] != '\0') {
				/* Found junk after ".." */
				free(estr);
				goto bad_modifier;
			    }
			} else {
			    /* Found junk instead of ".." */
			    free(estr);
			    goto bad_modifier;
			}
			/*
			 * Now seldata is properly filled in,
			 * but we still have to check for 0 as
			 * a special case.
			 */
			if (seldata.start == 0 && seldata.end == 0) {
			    /* ":[0]" or perhaps ":[0..0]" */
			    parsestate.oneBigWord = TRUE;
			    newStr = nstr;
			    termc = *cp;
			    free(estr);
			    break;
			} else if (seldata.start == 0 ||
				   seldata.end == 0) {
			    /* ":[0..N]" or ":[N..0]" */
			    free(estr);
			    goto bad_modifier;
			}
			/*
			 * Normal case: select the words
			 * described by seldata.
			 */
			newStr = VarSelectWords(ctxt, &parsestate,
						nstr, &seldata);

			termc = *cp;
			free(estr);
			break;
		    }

		}
	        case 't':
		{
		    cp = tstr + 1;	/* make sure it is set */
		    if (tstr[1] != endc && tstr[1] != ':') {
			if (tstr[1] == 's') {
			    /*
			     * Use the char (if any) at tstr[2]
			     * as the word separator.
			     */
			    VarPattern pattern;

			    if (tstr[2] != endc &&
				(tstr[3] == endc || tstr[3] == ':')) {
				/* ":ts<unrecognised><endc>" or
				 * ":ts<unrecognised>:" */
				parsestate.varSpace = tstr[2];
				cp = tstr + 3;
			    } else if (tstr[2] == endc || tstr[2] == ':') {
				/* ":ts<endc>" or ":ts:" */
				parsestate.varSpace = 0; /* no separator */
				cp = tstr + 2;
			    } else if (tstr[2] == '\\') {
				switch (tstr[3]) {
				case 'n':
				    parsestate.varSpace = '\n';
				    cp = tstr + 4;
				    break;
				case 't':
				    parsestate.varSpace = '\t';
				    cp = tstr + 4;
				    break;
				default:
				    if (isdigit((unsigned char)tstr[3])) {
					char *ep;
					
					parsestate.varSpace =
						strtoul(&tstr[3], &ep, 0);
					if (*ep != ':' && *ep != endc)
					    goto bad_modifier;
					cp = ep;
				    } else {
					/*
					 * ":ts<backslash><unrecognised>".
					 */
					goto bad_modifier;
				    }
				    break;
				}
			    } else {
				/*
				 * Found ":ts<unrecognised><unrecognised>".
				 */
				goto bad_modifier;
			    }

			    termc = *cp;

			    /*
			     * We cannot be certain that VarModify
			     * will be used - even if there is a
			     * subsequent modifier, so do a no-op
			     * VarSubstitute now to for str to be
			     * re-expanded without the spaces.
			     */
			    pattern.flags = VAR_SUB_ONE;
			    pattern.lhs = pattern.rhs = "\032";
			    pattern.leftLen = pattern.rightLen = 1;

			    newStr = VarModify(ctxt, &parsestate, nstr,
					       VarSubstitute,
					       (ClientData)&pattern);
			} else if (tstr[2] == endc || tstr[2] == ':') {
			    /*
			     * Check for two-character options:
			     * ":tu", ":tl"
			     */
                            if (tstr[1] == 'u' || tstr[1] == 'l') {
                                newStr = VarChangeCase(nstr, (tstr[1] == 'u'));
                                cp = tstr + 2;
                                termc = *cp;
                            } else if (tstr[1] == 'W' || tstr[1] == 'w') {
				parsestate.oneBigWord = (tstr[1] == 'W');
				newStr = nstr;
				cp = tstr + 2;
				termc = *cp;
                            } else {
				/* Found ":t<unrecognised>:" or
				 * ":t<unrecognised><endc>". */
				goto bad_modifier;
			    }
			} else {
			    /*
			     * Found ":t<unrecognised><unrecognised>".
			     */
			    goto bad_modifier;
			}
		    } else {
			/*
			 * Found ":t<endc>" or ":t:".
			 */
			goto bad_modifier;
		    }
		    break;
		}
		case 'N':
		case 'M':
		{
		    char    *pattern;
		    char    *cp2;
		    Boolean copy;
		    int nest;

		    copy = FALSE;
		    nest = 1;
		    /*
		     * In the loop below, ignore ':' unless we are at
		     * (or back to) the original brace level.
		     * XXX This will likely not work right if $() and ${}
		     * are intermixed.
		     */
		    for (cp = tstr + 1;
			 *cp != '\0' && !(*cp == ':' && nest == 1);
			 cp++)
		    {
			if (*cp == '\\' &&
			    (cp[1] == ':' ||
			     cp[1] == endc || cp[1] == startc)) {
			    copy = TRUE;
			    cp++;
			    continue;
			}
			if (*cp == startc)
			    ++nest;
			if (*cp == endc) {
			    --nest;
			    if (nest == 0)
				break;
			}
		    }
		    termc = *cp;
		    *WR(cp) = '\0';
		    if (copy) {
			/*
			 * Need to compress the \:'s out of the pattern, so
			 * allocate enough room to hold the uncompressed
			 * pattern (note that cp started at tstr+1, so
			 * cp - tstr takes the null byte into account) and
			 * compress the pattern into the space.
			 */
			pattern = emalloc(cp - tstr);
			for (cp2 = pattern, cp = tstr + 1;
			     *cp != '\0';
			     cp++, cp2++)
			{
			    if ((*cp == '\\') &&
				(cp[1] == ':' || cp[1] == endc)) {
				    cp++;
			    }
			    *cp2 = *cp;
			}
			*cp2 = '\0';
		    } else {
			pattern = UNCONST(&tstr[1]);
		    }
		    if ((cp2 = strchr(pattern, '$'))) {
			cp2 = pattern;
			pattern = Var_Subst(NULL, cp2, ctxt, err);
			if (copy)
			    free(cp2);
			copy = TRUE;
		    }
		    if (*tstr == 'M' || *tstr == 'm') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarMatch,
					   (ClientData)pattern);
		    } else {
			newStr = VarModify(ctxt, &parsestate, nstr, VarNoMatch,
					   (ClientData)pattern);
		    }
		    if (copy) {
			free(pattern);
		    }
		    break;
		}
		case 'S':
		{
		    VarPattern 	    pattern;
		    Var_Parse_State tmpparsestate;

		    pattern.flags = 0;
		    tmpparsestate = parsestate;
		    delim = tstr[1];
		    tstr += 2;

		    /*
		     * If pattern begins with '^', it is anchored to the
		     * start of the word -- skip over it and flag pattern.
		     */
		    if (*tstr == '^') {
			pattern.flags |= VAR_MATCH_START;
			tstr += 1;
		    }

		    cp = tstr;
		    if ((pattern.lhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim,
						     &pattern.flags,
						     &pattern.leftLen,
						     NULL)) == NULL)
			goto cleanup;

		    if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.rightLen,
						     &pattern)) == NULL)
			goto cleanup;

		    /*
		     * Check for global substitution. If 'g' after the final
		     * delimiter, substitution is global and is marked that
		     * way.
		     */
		    for (;; cp++) {
			switch (*cp) {
			case 'g':
			    pattern.flags |= VAR_SUB_GLOBAL;
			    continue;
			case '1':
			    pattern.flags |= VAR_SUB_ONE;
			    continue;
			case 'W':
			    tmpparsestate.oneBigWord = TRUE;
			    continue;
			}
			break;
		    }

		    termc = *cp;
		    newStr = VarModify(ctxt, &tmpparsestate, nstr,
				       VarSubstitute,
				       (ClientData)&pattern);

		    /*
		     * Free the two strings.
		     */
		    free(UNCONST(pattern.lhs));
		    free(UNCONST(pattern.rhs));
		    delim = '\0';
		    break;
		}	
		case '?':
		{
		    VarPattern 	pattern;
		    Boolean	value;

		    /* find ':', and then substitute accordingly */

		    pattern.flags = 0;

		    cp = ++tstr;
		    delim = ':';
		    if ((pattern.lhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.leftLen,
						     NULL)) == NULL)
			goto cleanup;

			/* BROPEN or PROPEN */
		    delim = endc;
		    if ((pattern.rhs = VarGetPattern(ctxt, &parsestate, err,
						     &cp, delim, NULL,
						     &pattern.rightLen,
						     NULL)) == NULL)
			goto cleanup;

		    termc = *--cp;
		    delim = '\0';
		    if (Cond_EvalExpression(1, v->name, &value, 0)
			== COND_INVALID) {
			Error("Bad conditional expression `%s' in %s?%s:%s",
			      v->name, v->name, pattern.lhs, pattern.rhs);
			goto cleanup;
		    }

		    if (value) {
			newStr = UNCONST(pattern.lhs);
			free(UNCONST(pattern.rhs));
		    } else {
			newStr = UNCONST(pattern.rhs);
			free(UNCONST(pattern.lhs));
		    }
		    if (v->flags & VAR_JUNK) {
			v->flags |= VAR_KEEP;
		    }
		    break;
		}
#ifndef NO_REGEX
		case 'C':
		{
		    VarREPattern    pattern;
		    char           *re;
		    int             error;
		    Var_Parse_State tmpparsestate;

		    pattern.flags = 0;
		    tmpparsestate = parsestate;
		    delim = tstr[1];
		    tstr += 2;

		    cp = tstr;

		    if ((re = VarGetPattern(ctxt, &parsestate, err, &cp, delim,
					    NULL, NULL, NULL)) == NULL)
			goto cleanup;

		    if ((pattern.replace = VarGetPattern(ctxt, &parsestate,
							 err, &cp, delim, NULL,
							 NULL, NULL)) == NULL){
			free(re);
			goto cleanup;
		    }

		    for (;; cp++) {
			switch (*cp) {
			case 'g':
			    pattern.flags |= VAR_SUB_GLOBAL;
			    continue;
			case '1':
			    pattern.flags |= VAR_SUB_ONE;
			    continue;
			case 'W':
			    tmpparsestate.oneBigWord = TRUE;
			    continue;
			}
			break;
		    }

		    termc = *cp;

		    error = regcomp(&pattern.re, re, REG_EXTENDED);
		    free(re);
		    if (error)  {
			*lengthPtr = cp - start + 1;
			VarREError(error, &pattern.re, "RE substitution error");
			free(pattern.replace);
			return (var_Error);
		    }

		    pattern.nsub = pattern.re.re_nsub + 1;
		    if (pattern.nsub < 1)
			pattern.nsub = 1;
		    if (pattern.nsub > 10)
			pattern.nsub = 10;
		    pattern.matches = emalloc(pattern.nsub *
					      sizeof(regmatch_t));
		    newStr = VarModify(ctxt, &tmpparsestate, nstr,
				       VarRESubstitute,
				       (ClientData) &pattern);
		    regfree(&pattern.re);
		    free(pattern.replace);
		    free(pattern.matches);
		    delim = '\0';
		    break;
		}
#endif
		case 'Q':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarQuote(nstr);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'T':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarTail,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'H':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarHead,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'E':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarSuffix,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'R':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarModify(ctxt, &parsestate, nstr, VarRoot,
					   (ClientData)0);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
		case 'O':
		{
		    char otype;

		    cp = tstr + 1;	/* skip to the rest in any case */
		    if (tstr[1] == endc || tstr[1] == ':') {
			otype = 's';
			termc = *cp;
		    } else if ( (tstr[1] == 'x') &&
		    		(tstr[2] == endc || tstr[2] == ':') ) {
			otype = tstr[1];
			cp = tstr + 2;
			termc = *cp;
		    } else {
			goto bad_modifier;
		    }
		    newStr = VarOrder(nstr, otype);
		    break;
		}
		case 'u':
		    if (tstr[1] == endc || tstr[1] == ':') {
			newStr = VarUniq(nstr);
			cp = tstr + 1;
			termc = *cp;
			break;
		    }
		    goto default_case;
#ifdef SUNSHCMD
		case 's':
		    if (tstr[1] == 'h' && (tstr[2] == endc || tstr[2] == ':')) {
			const char *emsg;
			newStr = Cmd_Exec(nstr, &emsg);
			if (emsg)
			    Error(emsg, nstr);
			cp = tstr + 2;
			termc = *cp;
			break;
		    }
		    goto default_case;
#endif
                default:
		default_case: 
		{
#ifdef SYSVVARSUB
		    /*
		     * This can either be a bogus modifier or a System-V
		     * substitution command.
		     */
		    VarPattern      pattern;
		    Boolean         eqFound;

		    pattern.flags = 0;
		    eqFound = FALSE;
		    /*
		     * First we make a pass through the string trying
		     * to verify it is a SYSV-make-style translation:
		     * it must be: <string1>=<string2>)
		     */
		    cp = tstr;
		    cnt = 1;
		    while (*cp != '\0' && cnt) {
			if (*cp == '=') {
			    eqFound = TRUE;
			    /* continue looking for endc */
			}
			else if (*cp == endc)
			    cnt--;
			else if (*cp == startc)
			    cnt++;
			if (cnt)
			    cp++;
		    }
		    if (*cp == endc && eqFound) {

			/*
			 * Now we break this sucker into the lhs and
			 * rhs. We must null terminate them of course.
			 */
			delim='=';
			cp = tstr;
			if ((pattern.lhs = VarGetPattern(ctxt, &parsestate, 
				err, &cp, delim, &pattern.flags,
				&pattern.leftLen, NULL)) == NULL)
				goto cleanup;
			delim = endc;
			if ((pattern.rhs = VarGetPattern(ctxt, &parsestate,
				err, &cp, delim, NULL, &pattern.rightLen,
				&pattern)) == NULL)
				goto cleanup;

			/*
			 * SYSV modifications happen through the whole
			 * string. Note the pattern is anchored at the end.
			 */
			termc = *--cp;
			delim = '\0';
			newStr = VarModify(ctxt, &parsestate, nstr,
					   VarSYSVMatch,
					   (ClientData)&pattern);
			free(UNCONST(pattern.lhs));
			free(UNCONST(pattern.rhs));
		    } else
#endif
		    {
			Error("Unknown modifier '%c'", *tstr);
			for (cp = tstr+1;
			     *cp != ':' && *cp != endc && *cp != '\0';
			     cp++)
				 continue;
			termc = *cp;
			newStr = var_Error;
		    }
		}
	    }
	    if (DEBUG(VAR)) {
		printf("Result is \"%s\"\n", newStr);
	    }

	    if (newStr != nstr) {
		if (*freePtr) {
		    free(nstr);
		}
		nstr = newStr;
		if (nstr != var_Error && nstr != varNoError) {
		    *freePtr = TRUE;
		} else {
		    *freePtr = FALSE;
		}
	    }
	    if (termc == '\0') {
		Error("Unclosed variable specification for %s", v->name);
	    } else if (termc == ':') {
		*WR(cp) = termc;
		cp++;
	    } else {
		*WR(cp) = termc;
	    }
	    tstr = cp;
	}
	*lengthPtr = tstr - start + 1;
    } else {
	*lengthPtr = tstr - start + 1;
	*WR(tstr) = endc;
    }

    if (v->flags & VAR_FROM_ENV) {
	Boolean	  destroy = FALSE;

	if (nstr != (char *)Buf_GetAll(v->val, NULL)) {
	    destroy = TRUE;
	} else {
	    /*
	     * Returning the value unmodified, so tell the caller to free
	     * the thing.
	     */
	    *freePtr = TRUE;
	}
	if (nstr != (char *)Buf_GetAll(v->val, NULL))
	    Buf_Destroy(v->val, destroy);
	free(v->name);
	free(v);
    } else if (v->flags & VAR_JUNK) {
	/*
	 * Perform any free'ing needed and set *freePtr to FALSE so the caller
	 * doesn't try to free a static pointer.
	 * If VAR_KEEP is also set then we want to keep str as is.
	 */
	if (!(v->flags & VAR_KEEP)) {
	    if (*freePtr) {
		free(nstr);
	    }
	    *freePtr = FALSE;
	    if (dynamic) {
		nstr = emalloc(*lengthPtr + 1);
		strncpy(nstr, start, *lengthPtr);
		nstr[*lengthPtr] = '\0';
		*freePtr = TRUE;
	    } else {
		nstr = var_Error;
	    }
	}
	if (nstr != (char *)Buf_GetAll(v->val, NULL))
	    Buf_Destroy(v->val, TRUE);
	free(v->name);
	free(v);
    }
    return (nstr);

 bad_modifier:
							/* "{(" */
    Error("Bad modifier `:%.*s' for %s", (int)strcspn(tstr, ":)}"), tstr,
	  v->name);

cleanup:
    *lengthPtr = cp - start + 1;
    if (*freePtr)
	free(nstr);
    if (delim != '\0')
	Error("Unclosed substitution for %s (%c missing)",
	      v->name, delim);
    return (var_Error);
}

/*-
 *-----------------------------------------------------------------------
 * Var_Subst  --
 *	Substitute for all variables in the given string in the given context
 *	If undefErr is TRUE, Parse_Error will be called when an undefined
 *	variable is encountered.
 *
 * Input:
 *	var		Named variable || NULL for all
 *	str		the string which to substitute
 *	ctxt		the context wherein to find variables
 *	undefErr	TRUE if undefineds are an error
 *
 * Results:
 *	The resulting string.
 *
 * Side Effects:
 *	None. The old string must be freed by the caller
 *-----------------------------------------------------------------------
 */
char *
Var_Subst(const char *var, const char *str, GNode *ctxt, Boolean undefErr)
{
    Buffer  	  buf;	    	    /* Buffer for forming things */
    char    	  *val;		    /* Value to substitute for a variable */
    int	    	  length;   	    /* Length of the variable invocation */
    Boolean	  trailingBslash;   /* variable ends in \ */
    Boolean 	  doFree;   	    /* Set true if val should be freed */
    static Boolean errorReported;   /* Set true if an error has already
				     * been reported to prevent a plethora
				     * of messages when recursing */

    buf = Buf_Init(MAKE_BSIZE);
    errorReported = FALSE;
    trailingBslash = FALSE;

    while (*str) {
	if (*str == '\n' && trailingBslash)
	    Buf_AddByte(buf, ' ');
	if (var == NULL && (*str == '$') && (str[1] == '$')) {
	    /*
	     * A dollar sign may be escaped either with another dollar sign.
	     * In such a case, we skip over the escape character and store the
	     * dollar sign into the buffer directly.
	     */
	    str++;
	    Buf_AddByte(buf, (Byte)*str);
	    str++;
	} else if (*str != '$') {
	    /*
	     * Skip as many characters as possible -- either to the end of
	     * the string or to the next dollar sign (variable invocation).
	     */
	    const char  *cp;

	    for (cp = str++; *str != '$' && *str != '\0'; str++)
		continue;
	    Buf_AddBytes(buf, str - cp, (const Byte *)cp);
	} else {
	    if (var != NULL) {
		int expand;
		for (;;) {
		    if (str[1] == '\0') {
			/* A trailing $ is kind of a special case */
			Buf_AddByte(buf, str[0]);
			str++;
			expand = FALSE;
		    } else if (str[1] != PROPEN && str[1] != BROPEN) {
			if (str[1] != *var || strlen(var) > 1) {
			    Buf_AddBytes(buf, 2, (const Byte *)str);
			    str += 2;
			    expand = FALSE;
			}
			else
			    expand = TRUE;
			break;
		    }
		    else {
			const char *p;

			/*
			 * Scan up to the end of the variable name.
			 */
			for (p = &str[2]; *p &&
			     *p != ':' && *p != PRCLOSE && *p != BRCLOSE; p++)
			    if (*p == '$')
				break;
			/*
			 * A variable inside the variable. We cannot expand
			 * the external variable yet, so we try again with
			 * the nested one
			 */
			if (*p == '$') {
			    Buf_AddBytes(buf, p - str, (const Byte *)str);
			    str = p;
			    continue;
			}

			if (strncmp(var, str + 2, p - str - 2) != 0 ||
			    var[p - str - 2] != '\0') {
			    /*
			     * Not the variable we want to expand, scan
			     * until the next variable
			     */
			    for (;*p != '$' && *p != '\0'; p++)
				continue;
			    Buf_AddBytes(buf, p - str, (const Byte *)str);
			    str = p;
			    expand = FALSE;
			}
			else
			    expand = TRUE;
			break;
		    }
		}
		if (!expand)
		    continue;
	    }

	    val = Var_Parse(str, ctxt, undefErr, &length, &doFree);

	    /*
	     * When we come down here, val should either point to the
	     * value of this variable, suitably modified, or be NULL.
	     * Length should be the total length of the potential
	     * variable invocation (from $ to end character...)
	     */
	    if (val == var_Error || val == varNoError) {
		/*
		 * If performing old-time variable substitution, skip over
		 * the variable and continue with the substitution. Otherwise,
		 * store the dollar sign and advance str so we continue with
		 * the string...
		 */
		if (oldVars) {
		    str += length;
		} else if (undefErr) {
		    /*
		     * If variable is undefined, complain and skip the
		     * variable. The complaint will stop us from doing anything
		     * when the file is parsed.
		     */
		    if (!errorReported) {
			Parse_Error(PARSE_FATAL,
				     "Undefined variable \"%.*s\"",length,str);
		    }
		    str += length;
		    errorReported = TRUE;
		} else {
		    Buf_AddByte(buf, (Byte)*str);
		    str += 1;
		}
	    } else {
		/*
		 * We've now got a variable structure to store in. But first,
		 * advance the string pointer.
		 */
		str += length;

		/*
		 * Copy all the characters from the variable value straight
		 * into the new string.
		 */
		length = strlen(val);
		Buf_AddBytes(buf, length, (Byte *)val);
		trailingBslash = length > 0 && val[length - 1] == '\\';
		if (doFree) {
		    free(val);
		}
	    }
	}
    }

    Buf_AddByte(buf, '\0');
    val = (char *)Buf_GetAll(buf, NULL);
    Buf_Destroy(buf, FALSE);
    return (val);
}

/*-
 *-----------------------------------------------------------------------
 * Var_GetTail --
 *	Return the tail from each of a list of words. Used to set the
 *	System V local variables.
 *
 * Input:
 *	file		Filename to modify
 *
 * Results:
 *	The resulting string.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
#if 0
char *
Var_GetTail(char *file)
{
    return(VarModify(file, VarTail, (ClientData)0));
}

/*-
 *-----------------------------------------------------------------------
 * Var_GetHead --
 *	Find the leading components of a (list of) filename(s).
 *	XXX: VarHead does not replace foo by ., as (sun) System V make
 *	does.
 *
 * Input:
 *	file		Filename to manipulate
 *
 * Results:
 *	The leading components.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
char *
Var_GetHead(char *file)
{
    return(VarModify(file, VarHead, (ClientData)0));
}
#endif

/*-
 *-----------------------------------------------------------------------
 * Var_Init --
 *	Initialize the module
 *
 * Results:
 *	None
 *
 * Side Effects:
 *	The VAR_CMD and VAR_GLOBAL contexts are created
 *-----------------------------------------------------------------------
 */
void
Var_Init(void)
{
    VAR_GLOBAL = Targ_NewGN("Global");
    VAR_CMD = Targ_NewGN("Command");

}


void
Var_End(void)
{
}


/****************** PRINT DEBUGGING INFO *****************/
static void
VarPrintVar(ClientData vp)
{
    Var    *v = (Var *)vp;
    printf("%-16s = %s\n", v->name, (char *)Buf_GetAll(v->val, NULL));
}

/*-
 *-----------------------------------------------------------------------
 * Var_Dump --
 *	print all variables in a context
 *-----------------------------------------------------------------------
 */
void
Var_Dump(GNode *ctxt)
{
    Hash_Search search;
    Hash_Entry *h;

    for (h = Hash_EnumFirst(&ctxt->context, &search);
	 h != NULL;
	 h = Hash_EnumNext(&search)) {
	    VarPrintVar(Hash_GetValue(h));
    }
}
