#include <iostream>

using std::cerr;

#pragma once

#define KTL_CDBG_COLOR_INIT    "\033[1;33m"
#define KTL_CDBG_COLOR_DEINIT  "\033[0m"

#define note(x) #x << " = " << (x)
#define short_pos() "[" << __LINE__ << "]"
#define long_pos() "[<" << __PRETTY_FUNCTION__ << ">::" << __LINE__ << "]"
#if defined(XHOVA) && !defined(XHOVA_O)
#define cdbg(...)  cerr << KTL_CDBG_COLOR_INIT << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT
#define cdbgx(...) cerr << KTL_CDBG_COLOR_INIT << short_pos() << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT
#define cdbgX(...) cerr << KTL_CDBG_COLOR_INIT <<  long_pos() << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT
#else
#define cdbg(...) 0
#define cdbgx(...) 0
#define cdbgX(...) 0
#endif
