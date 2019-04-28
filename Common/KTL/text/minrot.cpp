// Lexicographically minimal rotation via Lyndon factorization
// with Duval's algorithm.
// Complexity: O(n)
// Last revision: April 2019

#pragma once

#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;

template<typename String, typename Compare = less<T>>
size_t min_rotation(const String& Z, Compare cmp = {})
{
    using T = String::value_type;
    String S = Z + Z;
    const size_t n = S.size();
    size_t i = 0, r = 0;
    while(i < n / 2)
    {
        r = i;
        size_t j = i + 1, k = i;
        while(j < n and (cmp(S[k], S[j]) or S[k] == S[j]))
        {
            if(cmp(S[k], S[j]))
                k = i;
            else
                k++;
            j++;
        }
        while(i <= k)
            i += j - k;
    }
    return r;
}
