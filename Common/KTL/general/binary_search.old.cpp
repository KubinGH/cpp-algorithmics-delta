// Last revision: Around the end of 2017

#pragma once

#include <cstddef>
using std::size_t;

// Binary search
// Note: faster than STL's std::lower_bound, std::upper_bound
template<typename T>
T own_lower_bound(T A[], size_t n, T a)
{
    size_t lo = 0, hi = n;
    while(lo < hi)
    {
        size_t mid = (lo + hi) / 2;
        if(A[mid] >= a) // replace with any monotonic function
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}
