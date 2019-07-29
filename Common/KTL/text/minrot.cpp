// Lexicographically minimal rotation via Lyndon factorization
// with Duval's algorithm.
// Complexity: O(n)

// Last revision: July 2019

#pragma once

#include <functional>
#include <iterator>
#include <cstddef>
#include <vector>

using std::less;
using std::size_t;
using std::vector;
using std::iterator_traits;

template<
    typename Iterator,
    typename T = typename iterator_traits<Iterator>::value_type,
    typename Compare = less<T>
>
size_t min_rotation(Iterator first, Iterator last, Compare cmp = {})
{
    const size_t n = distance(first, last) * 2;
    vector<T> S(2*n);
    copy(first, last, S.begin());
    copy(S.begin(), S.end(), S.begin() + n);
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
