#pragma once

#include <iostream>

using std::cerr;
using std::flush;
using std::endl;
using std::ostream;

#ifndef KTL_DEBUG_MACROS
#if defined(XHOVA) && !defined(XHOVA_O)
#define KTL_DEBUG_MACROS
#endif
#endif

#define KTL_CDBG_COLOR_INIT    "\033[1;33m"
#define KTL_CDBG_COLOR_DEINIT  "\033[0m"

#define note(x) #x << " = " << (x)
#define short_pos "[" << __LINE__ << "]"
#define long_pos "[<" << __PRETTY_FUNCTION__ << ">::" << __LINE__ << "]"
#ifdef KTL_DEBUG_MACROS
#define debug(...)  cerr << KTL_CDBG_COLOR_INIT << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << flush
#define debugx(...) cerr << KTL_CDBG_COLOR_INIT << short_pos << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#define debugX(...) cerr << KTL_CDBG_COLOR_INIT <<  long_pos << ": " << __VA_ARGS__ << KTL_CDBG_COLOR_DEINIT << endl
#else
#define debug(...) (void)0
#define debugx(...) (void)0
#define debugX(...) (void)0
#endif

struct cdbg_t
{
    template<typename T>
    cdbg_t& operator<< (const T& o)
    {
        (void)o;
#ifdef KTL_DEBUG_MACROS
        debug(o);
#endif
        return *this;
    }
    cdbg_t& operator<< (ostream& (*pf)(ostream&))
    {
        (void)pf;
#ifdef KTL_DEBUG_MACROS
        debug(pf);
#endif
        return *this;
    }
} cdbg;
