// Prefixosuffixes

// Last revision: December 2018

#pragma once

#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;

template<typename Iterator>
vector<size_t> prefixosuffixes(Iterator first, Iterator last)
{
    const size_t n = distance(first, last);
    vector<size_t> P(n);
    P[0] = 0;
    for(size_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and first[P[i]] != first[i])
            P[i] = P[P[i] - 1];
        if(first[i] == first[P[i]])
            P[i]++;
    }
    return P;
}
