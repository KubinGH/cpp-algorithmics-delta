// Binary search based around placing a pivot
// in the middle of the range, instead of
// STL's exponential search. This approach
// tends to be faster.

// Last revision: October 2018

#pragma once

#include <cstddef>
using std::size_t;

#define BINARY_SEARCH_BODY_COND(_Arg, _expr, _cond, _eps)    \
{                                   \
    while(_cond)                    \
    {                               \
        _Arg mid = (lo + hi) / 2;   \
        if(_expr)                   \
            hi = mid;               \
        else                        \
            lo = mid + _eps;        \
    }                               \
    return lo;                      \
}
#define BINARY_SEARCH_BODY(_Arg, _expr) BINARY_SEARCH_BODY_COND(_Arg, _expr, (lo < hi), 1)

// standard, iterator-based
template<typename T, typename Iterator>
Iterator q_lower_bound(Iterator lo, Iterator hi, T value)
{
    BINARY_SEARCH_BODY(Iterator, *mid >= value)
}
template<typename T, typename Iterator>
Iterator q_upper_bound(Iterator lo, Iterator hi, T value)
{
    BINARY_SEARCH_BODY(Iterator, *mid > value)
}

// generalized operation
template<typename Arg, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f)
{
    BINARY_SEARCH_BODY(Arg, f(mid))
}
template<typename Arg, typename Result>
Arg first_true(Arg lo, Arg hi, Result(*f)(Arg))
{
    BINARY_SEARCH_BODY(Arg, f(mid))
}

// generalized operation & epsilon
template<typename Arg, typename Result, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f, Arg epsilon)
{
    BINARY_SEARCH_BODY_COND(Arg, f(mid), (hi - lo > epsilon), epsilon)
}
template<typename Arg, typename Result>
Arg first_true(Arg lo, Arg hi, Result(*f)(Arg), Arg epsilon)
{
    BINARY_SEARCH_BODY_COND(Arg, f(mid), (hi - lo > epsilon), epsilon)
}



