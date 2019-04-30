#include <iostream>

using std::cerr;
using std::endl;

#pragma once

#define KTL_CDBG_COLOR_INIT    "\033[1;33m"
#define KTL_CDBG_COLOR_DEINIT  "\033[0m"

#define note(x) #x << " = " << (x)
#define short_pos() "[" << __LINE__ << "]"
#define long_pos() "[<" << __PRETTY_FUNCTION__ << ">::" << __LINE__ << "]"
#if defined(XHOVA) && !defined(XHOVA_O)
#define debug(...)  cerr << KTL_CDBG_COLOR_INIT << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT
#define debugx(...) cerr << KTL_CDBG_COLOR_INIT << short_pos() << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#define debugX(...) cerr << KTL_CDBG_COLOR_INIT <<  long_pos() << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#else
#define debug(...) (void)0
#define debugx(...) (void)0
#define debugX(...) (void)0
#endif
