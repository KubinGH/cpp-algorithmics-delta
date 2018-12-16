// Prefixosuffixes

// Last revision: December 2018

#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

using std::size_t; using std::uint32_t;
using std::vector;

template<typename Iterator>
vector<uint32_t> prefixosuffixes(Iterator S, size_t n)
{
    vector<uint32_t> P(n);
    P[0] = 0;
    for(uint32_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[P[i]] != S[i]) P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]]) P[i]++;
    }
    return P;
}
