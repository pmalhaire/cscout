/* 
 * (C) Copyright 2001 Diomidis Spinellis.
 *
 * For documentation read the corresponding .h file
 *
 * $Id: error.cpp,v 1.1 2001/08/20 15:32:58 dds Exp $
 */

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <stack>
#include <deque>
#include <map>

#include "fileid.h"
#include "cpp.h"
#include "tokid.h"
#include "fchar.h"
#include "error.h"

int Error::num_errors;
int Error::num_warnings;


void
Error::error(enum e_error_level level, string msg)
{
	cerr << Fchar::get_path() << "(" << Fchar::get_line_num() << "): ";
	switch (level) {
	case E_WARN: cerr << "warning: "; break;
	case E_ERR: cerr << "error: "; break;
	case E_INTERNAL: cerr << "internal error: "; break;
	case E_FATAL: cerr << "fatal error: "; break;
	}
	cerr << msg << "\n";
	switch (level) {
	case E_WARN: num_warnings++; break;
	case E_ERR: num_errors++; break;
	case E_INTERNAL:
	case E_FATAL: exit(1);
	}
}

int
Error::get_num_errors(void)
{
	return num_errors;
}

int
Error::get_num_warnings(void)
{
	return num_warnings;
}

#ifdef UNIT_TEST

#include "token.h"
#include "ptoken.h"
#include "ytab.h"
#include "pltoken.h"

main()
{
	Fchar::set_input("test/toktest.c");

	Error::error(E_WARN, "Error at beginning of file");
	for (;;) {
		Pltoken t;

		t.template getnext<Fchar>();
		if (t.get_code() == EOF)
			break;
		cout << t;
	}
	Error::error(E_WARN, "Error at EOF");

	return (0);
}
#endif /* UNIT_TEST */