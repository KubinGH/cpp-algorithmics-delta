// Karp Miller Rosenberg
// allows to compute a perfect identifier id(s) for each substring,
// such that id(a) = id(b) <=> a = b
// This version also retains the property that id(a) < id(b) <=> a < b
// (lexicographical comparison)

#include <algorithm>
#include <iterator>
#include <cstddef>
#include <utility>
#include <numeric>
#include <vector>

using std::size_t;
using std::vector; using std::pair;
using std::iota; using std::copy; using std::sort;
using std::iterator_traits; using std::back_inserter;
using std::__lg;

struct karp_miller_rosenberg
{
    size_t n;
    vector<vector<size_t>> T;

    template<typename Iterator>
    karp_miller_rosenberg(Iterator first, Iterator last)
    {
        T.push_back(compressed(first, last));
        n = T[0].size();

        vector<vector<size_t>> buckets(n);
        for(size_t k = 1; (1u << k) <= n; k++)
        {
            const size_t p = 1 << k, q = p >> 1, m = n - p + 1;
            vector<size_t> run(m);
            iota(run.begin(), run.end(), 0);

            auto bucketify = [&]() {
                run.clear();
                for(size_t v = 0; v < n; v++)
                {
                    for(const auto& w : buckets[v])
                        run.push_back(w);
                    buckets[v].clear();
                }
            };
            for(size_t i : run)
                buckets[T[k-1][i + q]].push_back(i);
            bucketify();
            for(size_t i : run)
                buckets[T[k-1][i]].push_back(i);
            bucketify();

            T.emplace_back(m);
            for(size_t i = 0, f = 0; i < m; i++)
            {
                if(i and T[k-1][run[i-1]] == T[k-1][run[i]]
                     and T[k-1][run[i-1] + q] == T[k-1][run[i] + q])
                    f++;
                T[k][run[i]] = i - f;
            }
        }
    }


    pair<size_t, size_t> operator() (size_t i, size_t j) const
    {
        const size_t d = j - i, e = __lg(d);
        return {T[e][i], T[e][j - (1 << e)]};
    }


    template<typename Iterator, typename V = typename iterator_traits<Iterator>::value_type>
    static vector<size_t> compressed(Iterator first, Iterator last)
    {
        const size_t n = distance(first, last);

        vector<pair<V, size_t>> values; values.reserve(n);
        for(size_t i = 0; i < n; i++, ++first)
            values.emplace_back(*first, i);
        sort(values.begin(), values.end());

        vector<size_t> result(n);
        for(size_t i = 0, f = 0; i < n; i++)
        {
            if(i and values[i].first == values[i-1].first)
                f++;
            result[values[i].second] = i - f;
        }

        return result;
    }
};
