#include <bits/stdc++.h>

using namespace std;

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

int64_t sum_segment_minimums(const vector<int>& A, size_t a, size_t b)
{
    if(a == b) return 0;
    if(a+1 == b) return A[a];

    const size_t c = (a + b) / 2;
    auto result = sum_segment_minimums(A, a, c) + sum_segment_minimums(A, c, b);

    int64_t right_min_sum = 0;
    int rhs = A[c];
    for(size_t i = c; i < b; i++)
        rhs = min(A[i], rhs), right_min_sum += rhs;

    int lhs = A[c-1]; rhs = A[c];
    size_t t = c;
    for(size_t i = c; i --> a; )
    {
        lhs = min(lhs, A[i]);
        while(t < b and lhs <= rhs)
        {
            right_min_sum -= rhs;
            t++;
            rhs = min(rhs, t == b ? INT_MIN : A[t]);
        }
        auto p = t - c;
        result += right_min_sum + (int64_t)p * lhs;
    }

    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    karp_miller_rosenberg kmr(S.begin(), S.end());
    auto lcp = lcp_array(kmr, suffix_array(kmr));

    cout << sum_segment_minimums(vector<int>(lcp.begin(), lcp.end()), 0, lcp.size());
}
