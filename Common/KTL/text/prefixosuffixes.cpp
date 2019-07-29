// Prefixosuffixes
// Complexity: O(n)

// Last revision: July 2019

#pragma once

#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;

template<typename RandomAccessIterator>
vector<size_t> prefixosuffixes(RandomAccessIterator S, RandomAccessIterator last)
{
    const size_t n = distance(S, last);
    vector<size_t> P(n);
    P[0] = 0;
    for(size_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[P[i]] != S[i])
            P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]])
            P[i]++;
    }
    return P;
}
