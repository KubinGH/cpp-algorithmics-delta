// Karp Miller Rosenberg
// allows to compute a perfect identifier id(s) for each substring,
// such that id(a) = id(b) <=> a = b
// This version also retains the property that id(a) < id(b) <=> a < b
// (lexicographical comparison)
// take1 is a guarded read of T, returning 0 in case of out-of-bounds
// take0 is the unguarded version, used for consistency

// Last revision: July 2019

#pragma once

#include <functional>
#include <algorithm>
#include <cstddef>
#include <utility>
#include <numeric>
#include <vector>

using std::size_t;
using std::vector; using std::pair;
using std::iota; using std::sort;
using std::function;
using std::__lg;

struct karp_miller_rosenberg
{
    size_t n;
    vector<vector<size_t>> T;

    template<typename Iterator>
    karp_miller_rosenberg(Iterator first, Iterator last)
    {
        n = distance(first, last);
        vector<size_t> run(n);

        auto push_compressed = [&](function<bool(size_t)> prev_same) {
            T.emplace_back(n);
            for(size_t i = 0, f = -1; i < n; i++)
                T.back()[run[i]] = i - (i and prev_same(i) ? ++f : f);
        };

        iota(run.begin(), run.end(), 0);
        sort(run.begin(), run.end(), [&](size_t i, size_t j) {
            return first[i] < first[j];
        });
        push_compressed([&](size_t i) {
            return first[run[i]] == first[run[i-1]];
        });

        vector<vector<size_t>> buckets(n+1);
        for(size_t k = 1; (1u << k) <= n; k++)
        {
            const size_t p = 1 << k, q = p >> 1;
            iota(run.begin(), run.end(), 0);

            auto bucketify = [&]() {
                run.clear();
                for(size_t v = 0; v < buckets.size(); v++)
                {
                    for(const auto& w : buckets[v])
                        run.push_back(w);
                    buckets[v].clear();
                }
            };
            for(size_t i : run)
                buckets[take1(k-1, i + q)].push_back(i);
            bucketify();
            for(size_t i : run)
                buckets[take0(k-1, i)].push_back(i);
            bucketify();

            push_compressed([&](size_t i) {
                return take0(k-1, run[i-1]) == take0(k-1, run[i]) and
                       take1(k-1, run[i-1] + q) == take1(k-1, run[i] + q);
            });
        }
    }
    size_t take0(size_t k, size_t i) const { return T[k][i]; }
    size_t take1(size_t k, size_t i) const { return i<n ? T[k][i] : 0; }

    pair<size_t, size_t> operator() (size_t i, size_t j) const
    {
        const size_t d = j - i, e = __lg(d);
        return {take0(e, i), take1(e, j - (1 << e))};
    }
};
