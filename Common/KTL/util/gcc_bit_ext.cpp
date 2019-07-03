#pragma once

#define ADAPT_BIT_EXT_TO_TEMPLATE(__new_name, __name_int, __name_long, __name_llong) \
    unsigned __new_name(int x) { return __name_int(x); }                    \
    unsigned __new_name(unsigned int x) { return __name_int(x); }           \
    unsigned __new_name(long x) { return __name_long(x); }                  \
    unsigned __new_name(unsigned long x) { return __name_long(x); }         \
    unsigned __new_name(long long x) { return __name_llong(x); }            \
    unsigned __new_name(unsigned long long x) { return __name_llong(x); }

ADAPT_BIT_EXT_TO_TEMPLATE(popcount, __builtin_popcount, __builtin_popcountl, __builtin_popcountll)
ADAPT_BIT_EXT_TO_TEMPLATE(clz, __builtin_clz, __builtin_clzl, __builtin_clzll)
ADAPT_BIT_EXT_TO_TEMPLATE(ctz, __builtin_ctz, __builtin_ctzl, __builtin_ctzll)

#undef ADAPT_BIT_EXT_TO_TEMPLATE
