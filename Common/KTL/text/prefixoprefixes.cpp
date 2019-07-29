// Prefixoprefixes / Z Algorithm
// Complexity: O(n)

// Last revision: July 2019

#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;
using std::min;

template<typename RandomAccessIterator>
vector<size_t> prefixoprefixes(RandomAccessIterator S, RandomAccessIterator last)
{
    const size_t n = distance(S, last);
    vector<size_t> Z(n);
    for(size_t i = 1, L = 0, R = 0; i < n; i++)
    {
        if(i < R)
            Z[i] = min(R - i, Z[i - L]);
        while(i + Z[i] < n and S[Z[i]] == S[i + Z[i]])
            Z[i]++;
        if(i + Z[i] > R)
            L = i, R = i + Z[i];
    }
    return Z;
}
