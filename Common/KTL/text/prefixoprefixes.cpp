// Prefixoprefixes / Z Algorithm
// Complexity: O(n)
// Last revision: December 2018

#pragma once

#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;

template<typename Iterator>
vector<size_t> prefixoprefixes(Iterator S, size_t n)
{
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
