# $NetBSD: autoswc.mk,v 1.1.1.1 2004/02/21 23:03:02 jmmv Exp $
#
# autoswc - Generates system wide cache files for GNU autoconf
# Copyright (c) 2004 Julio M. Merino Vidal <jmmv@NetBSD.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name of author nor the names of its contributors may
#    be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

.if !defined(AUTOSWC_MK)
AUTOSWC_MK=		# defined

.  if !defined(AUTOSWC_DISABLE)
AUTOSWC_CACHE_FILE?=	@CACHEDIR@/config.cache.${AUTOSWC_CACHE_NAME}
AUTOSWC_CACHE_NAME?=	default

.    if exists(@SYSCONFDIR@/config.site)
AUTOSWC_CONFIG_SITE?=	@SYSCONFDIR@/config.site
.    else
AUTOSWC_CONFIG_SITE?=	@PREFIX@/share/autoswc/config.site
.    endif

CONFIGURE_ENV+=		AUTOSWC_CACHE_FILE="${AUTOSWC_CACHE_FILE}"
CONFIGURE_ENV+=		AUTOSWC_CACHE_NAME="${AUTOSWC_CACHE_NAME}"
CONFIGURE_ENV+=		CONFIG_SITE="${AUTOSWC_CONFIG_SITE}"
.  endif

.endif # AUTOSWC_MK
