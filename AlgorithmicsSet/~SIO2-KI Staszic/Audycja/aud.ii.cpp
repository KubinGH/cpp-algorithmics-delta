#include <bits/stdc++.h>

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


// -*- ktl/text/suffix_array.cpp -*-

#include <algorithm>
#include <iterator>
#include <utility>
#include <limits>
#include <vector>

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

// -$- ktl/text/suffix_array.cpp -$-


// -*- ktl/text/lcp.cpp -*-

#include <algorithm>
#include <cstddef>
#include <vector>

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

// -$- ktl/text/lcp.cpp -$-


// -*- ktl/structures/sparse_table.cpp -*-

#include <algorithm>
#include <cstddef>
#include <vector>
#include <cstdint>

using std::size_t;
using std::vector;
using std::__lg;

template<typename T, typename BinaryOperation>
struct sparse_table
{
    struct _identity { T operator() (const T& x) const { return x; } };
    BinaryOperation F;
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator, typename TransformOperation = _identity>
    sparse_table(Iterator first, Iterator last, BinaryOperation f = {},
                 TransformOperation t = {}) : F(f)
    {
        n = distance(first, last);
        A.emplace_back(distance(first, last));
        for(size_t i = 0; first != last; first++, i++)
            A[0][i] = t(*first);
        for(size_t i = 1; (1u << i) <= n; i++)
        {
            A.emplace_back(n - (1u << i) + 1);
            for(size_t j = 0; j + (1 << i) <= n; j++)
                A[i][j] = F(A[i-1][j], A[i-1][j + (1u << (i-1))]);
        }
    }
    T operator() (size_t a, size_t b)
    {
        size_t p = __lg(b - a);
        return F(A[p][a], A[p][b - (1 << p)]);
    }
};

// -$- ktl/structures/sparse_table.cpp -$-


using namespace std;

struct mins { size_t operator() (size_t a, size_t b) { return min(a, b); } };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;
    string S;
    S.reserve(2*n + 1);
    cin >> S;

    S.push_back('$');
    copy(S.rbegin()+1, S.rend(), back_inserter(S));

    karp_miller_rosenberg kmr(S.begin(), S.end());
    auto sarray = suffix_array(kmr), lcp = lcp_array(kmr, sarray);

    vector<size_t> rank(2*n + 1);
    for(size_t i = 0; i < 2*n + 1; i++)
        rank[sarray[i]] = i;

    sparse_table<size_t, mins> min_lcp(lcp.begin(), lcp.end());

    vector<size_t> count = {0, 0, 0};
    size_t result = 0;
    auto f = [&](size_t i) {
        return i < n ? 0 : (i > n ? 1 : 2);
    };
    for(size_t i = 0, j = 0; i < 2*n + 1; i++)
    {
        while(j < 2*n + 1 and not (count[0] and count[1]))
        {
            count[f(sarray[j])]++;
            j++;
        }
        if(count[0] and count[1])
            result = max(result, min_lcp(i, j - 1));
        count[f(sarray[i])]--;
    }

    cout << result;
}
