// Computes Suffix Array using KMR, in complexity O([kmr] + n log n).
// The KMR must be implemented so that id(a) < id(b) <=> a < b
// (identifier comparison is the same as lexicographical comparison)

// Last revision: July 2019

#pragma once

#include <algorithm>
#include <iterator>
#include <utility>
#include <limits>
#include <vector>
#include "kmr.cpp"

using std::sort; using std::copy;
using std::vector; using std::pair;
using std::iterator_traits; using std::back_inserter;
using std::numeric_limits;

vector<size_t> suffix_array(const karp_miller_rosenberg& kmr)
{
    const size_t n = kmr.n;
    vector<pair<pair<size_t, size_t>, size_t>> keys(n);
    for(size_t i = 0; i < n; i++)
        keys[i] = {kmr(i, i + n), i};
    sort(keys.begin(), keys.end());
    vector<size_t> result(n);
    for(size_t i = 0; i < n; i++)
        result[i] = keys[i].second;
    return result;
}
