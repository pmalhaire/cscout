#
# Create a token name map
#
# $Id: tokname.pl,v 1.1 2002/09/05 07:19:43 dds Exp $
#

open(IN, $ARGV[0]) || die;
open(STDOUT, ">$ARGV[1]") || die;
print "
/*
 * Automatically generated file.
 * Modify the generator $0 or
 * $ARGV[0] (or more probably the file that generated it)
 */

";
print '
#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <vector>
#include <cassert>

#include "cpp.h"
#include "fileid.h"
#include "tokid.h"
#include "token.h"

#include "ytab.h"


/*
 * Return the name of a token code
 */
string
Token::name() const
{
	switch (code) {
';
while (<IN>) {
	if (/\#\s*define\s+(\w+)\s+\d+/) {
		print "\tcase $1: return(\"$1\"); break;\n";
	}
}

print q# 
	default:
		if (code < 255) {
			string s;
			s = (char)code;
			return (s);
		} else {
			assert(0);
			return ("");
		}
	}
}
#;