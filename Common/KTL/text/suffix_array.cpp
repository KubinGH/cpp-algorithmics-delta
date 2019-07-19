// Computes Suffix Array using KMR, in complexity O([kmr] + n log n).
// The KMR must be implemented so that id(a) < id(b) <=> a < b
// (identifier comparison is the same as lexicographical comparison)

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
    const size_t n = kmr.n / 2;
    vector<pair<pair<size_t, size_t>, size_t>> keys(n);
    for(size_t i = 0; i < n; i++)
        keys[i] = {kmr(i, i + n), i};
    sort(keys.begin(), keys.end());
    vector<size_t> result(n);
    for(size_t i = 0; i < n; i++)
        result[i] = keys[i].second;
    return result;
}

template<typename Iterator, typename T = typename iterator_traits<Iterator>::value_type>
vector<size_t> suffix_array(Iterator first, Iterator last, T leaf = numeric_limits<T>::min())
{
    const size_t n = distance(first, last);
    vector<T> buf;
    buf.reserve(2*n);
    copy(first, last, back_inserter(buf));
    for(size_t i = 0; i < n; i++)
        buf.emplace_back(leaf);

    karp_miller_rosenberg kmr(buf.begin(), buf.end());

    return suffix_array(kmr);
}
