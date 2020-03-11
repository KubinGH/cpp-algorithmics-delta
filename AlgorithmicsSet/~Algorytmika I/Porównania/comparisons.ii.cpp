#include <iostream>
#include <string>

// -*- ktl/text/kmr.cpp -*-

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
            for(size_t i = 0, f = 1; i < n; i++)
                T.back()[run[i]] = (i and not prev_same(i) ? ++f : f);
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

// -$- ktl/text/kmr.cpp -$-


using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    karp_miller_rosenberg kmr(S.begin(), S.end());

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        size_t a, b, l;
        cin >> a >> b >> l; a--; b--;

        auto x = kmr(a, a + l), y = kmr(b, b + l);
        if(x < y)
            cout << "<\n";
        else if(x > y)
            cout << ">\n";
        else
            cout << "=\n";
    }
}
