// binary_search.cpp with formatted preprocessed macros.

// Last revision: October 2018
// Generated with http://coliru.stacked-crooked.com/ with g++ -E.

#pragma once

#include <cstddef>
using std::size_t;

template<typename T, typename Iterator>
Iterator q_lower_bound(Iterator lo, Iterator hi, T value)
{
    while(lo < hi)
    {
        Iterator mid = (lo + hi) / 2;
        if(*mid >= value)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}
template<typename T, typename Iterator>
Iterator q_upper_bound(Iterator lo, Iterator hi, T value)
{
    while(lo < hi)
    {
        Iterator mid = (lo + hi) / 2;
        if(*mid > value)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}


template<typename Arg, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f)
{
    while(lo < hi)
    {
        Arg mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}
// same
template<typename Arg, typename Result>
Arg first_true(Arg lo, Arg hi, Result(*f)(Arg))
{
    { while(lo < hi) { Arg mid = (lo + hi) / 2; if(f(mid)) hi = mid; else lo = mid + 1; } return lo; }
}


template<typename Arg, typename Result, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f, Arg epsilon)
{
    while(hi - lo > epsilon)
    {
        Arg mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid + epsilon;
    }
    return lo;
}
// same
template<typename Arg, typename Result>
Arg first_true(Arg lo, Arg hi, Result(*f)(Arg), Arg epsilon)
{
    { while(hi - lo > epsilon) { Arg mid = (lo + hi) / 2; if(f(mid)) hi = mid; else lo = mid + epsilon; } return lo; }
}
