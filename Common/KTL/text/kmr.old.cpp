// Knuth Miller Rabin - base substrings dictonary
// Works, but is unbearably slow

// Last revision: October 2018

#pragma once

#include <cstddef>
#include <vector>
#include <cstdint>
#include <utility>
#include <map>
#include <unordered_map>
#include <iterator>
#include <algorithm>

using std::size_t;
using std::vector; using std::pair;
using std::uint32_t; using std::uint64_t;
using std::unordered_map; using std::map;
using std::iterator_traits;
using std::__lg;

struct karp_miller_rosenberg
{
    struct hash_2size
    {
        size_t operator() (const pair<size_t, size_t>& p) const
        {
            return 313*31*17*13*11*
                   ((uint64_t(p.first<<16) * uint64_t(p.second)) % ((1llu<<31)-1));
        }
    };
    size_t n;
    vector<vector<size_t>> A;
    template<typename Iterator, typename T = typename iterator_traits<Iterator>::value_type>
    karp_miller_rosenberg(Iterator first, Iterator last)
    {
        n = distance(first, last);
        A.emplace_back(n);
        map<T, size_t> elems; size_t g = 0;
        for(size_t i = 0; first != last; first++, i++)
            A[0][i] = (elems.find(*first) == elems.end() ? elems[*first] = g++ : elems[*first]);
        unordered_map<pair<size_t, size_t>, size_t, hash_2size> dict;
        dict.reserve(4*n);
        for(size_t i = 1; (1u << i) <= n; i++)
        {
            dict.clear();
            size_t h = 0;
            A.emplace_back(n - (1u << i) + 1);
            for(size_t j = 0; j + (1 << i) <= n; j++)
            {
                pair<size_t, size_t> p = {A[i-1][j], A[i-1][j + (1u << (i-1))]};
                if(dict.find(p) == dict.end())
                    dict[p] = h++;
                A[i][j] = dict[p];
            }
        }
    }
    pair<size_t, size_t> operator() (size_t a, size_t b)
    {
        size_t p = __lg(b - a + 1);
        return {A[p][a], A[p][b + 1 - (1 << p)]};
    }
};
