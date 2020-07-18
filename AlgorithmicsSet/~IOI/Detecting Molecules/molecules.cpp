#include <bits/stdc++.h>

using namespace std;

vector<int> find_subset(int l, int u, vector<int> w)
{
    const size_t n = w.size();

    vector<pair<int, size_t>> v;
    for(size_t i = 0; i < n; i++)
        v.emplace_back(w[i], i);
    sort(v.begin(), v.end());

    sort(w.begin(), w.end());
    int a = w[0];
    for(auto& x : w)
        x -= a;

    vector<int64_t> s(n + 1), z(n + 1);
    for(size_t i = 0; i < n; i++)
        s[i+1] = s[i] + w[i], z[i+1] = z[i] + w[n-i-1];

    vector<int> result;
    for(size_t k = 1; result.empty() and k <= n; k++)
    {
        size_t lo = 0, hi = k+1;
        auto c = [&](size_t i) {
            return (int64_t)k*a + s[k-i] + z[i];
        };

        while(lo < hi)
        {
            auto mid = (lo + hi) / 2;
            if(c(mid) >= l)
                hi = mid;
            else
                lo = mid+1;
        }

        if(lo <= k and l <= c(lo) and c(lo) <= u)
        {
            result.reserve(k);
            copy(w.begin(), w.begin() + (k-lo), back_inserter(result));
            copy(w.end() - lo, w.end(), back_inserter(result));
            break;
        }
    }

    for(auto& x : result)
        x += a;

    vector<int> ind; ind.reserve(result.size());
    for(size_t i = 0, j = 0; i < n and j < result.size(); i++)
        if(v[i].first == result[j])
            ind.push_back(v[i].second), j++;

    return ind;
}
