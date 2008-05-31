#!/bin/sh
#	$NetBSD: siglist.sh,v 1.2 2008/05/31 16:47:37 tnn Exp $
#
# Script to generate a sorted, complete list of signals, suitable
# for inclusion in trap.c as array initializer.
#

set -e

in=tmpi$$.c
out=tmpo$$.c
ecode=1
trapsigs='0 1 2 13 15'
trap 'rm -f $in $out; trap 0; exit $ecode' $trapsigs

CPP="${1-cc -E}"

# The trap here to make up for a bug in bash (1.14.3(1)) that calls the trap
(trap $trapsigs;
 echo '#include "sh.h"';
 echo '	{ QwErTy SIGNALS , "DUMMY" , "hook for number of signals" },';
 sed -e '/^[	 ]*#/d' -e 's/^[	 ]*\([^ 	][^ 	]*\)[	 ][	 ]*\(.*[^ 	]\)[ 	]*$/#ifdef SIG\1\
	{ QwErTy .signal = SIG\1 , .name = "\1", .mess = "\2" },\
#endif/') > $in
$CPP $in  > $out
sed -n 's/{ QwErTy/{/p' < $out | awk '{print NR, $0}' | sort -k5n -k1n |
    sed 's/^[0-9]* //' |
    awk 'BEGIN { last=0; nsigs=0; }
	{
	    if ($4 ~ /^[0-9][0-9]*$/ && $5 == ",") {
		n = $4;
		if (n > 0 && n != last) {
		    while (++last < n) {
			printf "\t{ .signal = %d , .name = NULL, .mess = `Signal %d` } ,\n", last, last;
		    }
		    print;
		}
	    }
	}' |
    tr '`' '"' | grep -v '"DUMMY"'
ecode=0
