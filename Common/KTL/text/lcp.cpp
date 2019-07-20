// Longest Common Prefix (LCP)
// get_lcp(i, j, [kmr]) yields the LCP of suffixes starting
// at indices i, j in the string specified by the KMR
// lcp := lcp_array(kmr, sarray) (sarray is the suffix array)
// has the property such that
//  get_lcp(sarray[i], sarray[j]) = min(lcp[i:j])
// => get_lcp(i, j) = min(lcp[rank(i):rank(j)])

#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>
#include "kmr.cpp"
#include "suffix_array.cpp"

using std::size_t;
using std::max;
using std::vector;

size_t get_lcp(size_t i, size_t j, const karp_miller_rosenberg& kmr)
{
    const size_t n = kmr.n;
    const auto& T = kmr.T;
    size_t r = 0;
    for(size_t k = kmr.T.size(); k --> 0; )
        if(max(i, j) + r + (1<<k) <= n and T[k][i+r] == T[k][j+r])
            r += (1 << k);
    return r;
}

vector<size_t> lcp_array(const karp_miller_rosenberg& kmr, const vector<size_t>& sarray)
{
    const size_t n = sarray.size();
    vector<size_t> lcp(n - 1);
    for(size_t i = 0; i+1 < n; i++)
        lcp[i] = get_lcp(sarray[i], sarray[i+1], kmr);
    return lcp;
}
