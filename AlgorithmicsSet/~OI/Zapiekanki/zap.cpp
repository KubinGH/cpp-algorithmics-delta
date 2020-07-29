#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k; uint d;
    cin >> n >> k >> d;

    vector<uint> T(n);
    for(auto& t : T)
        cin >> t;

    vector<int64_t> S(n+1);
    for(size_t i = 0; i < n; i++)
        S[i+1] = S[i] + T[i];

    auto cost = [&](size_t m, size_t l, uint t) {
        return int64_t((int64_t)t*l) - (S[m] - S[m-l]);
    };

    static vector<pair<uint, int64_t>> dp[4096];
    dp[0].emplace_back(0, 0);

    vector<pair<uint, int64_t>> run;
    for(size_t m = 1; m <= n; m++)
    {
        run.clear();
        vector<size_t> I = {0};
        I.reserve(min(m, k) + 1);
        for(size_t l = 1; l <= m and l <= k; l++)
        {
            auto ii = lower_bound(dp[m-l].begin(), dp[m-l].end(), pair<uint, int64_t>{T[m-1]-d, 0}) - dp[m-l].begin();
            if(ii) ii--;
            if(ii) ii--;
            for(size_t i = ii; i < dp[m-l].size(); i++)
            {
                const auto& [t, r] = dp[m-l][i];
                auto t1 = max(t + d, T[m-1]);
                run.emplace_back(t1, r + cost(m, l, t1));
            }
            I.push_back(run.size());
        }
        auto cmp = [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first or (lhs.first == rhs.first and lhs.second > rhs.second);
        };

        function<void(size_t, size_t)> mergesort = [&](size_t l, size_t r) {
            if(l+1 >= r)
                return;
            mergesort(l, (l+r)/2);
            mergesort((l+r)/2, r);
            inplace_merge(run.begin() + I[l], run.begin() + I[(l+r)/2], run.begin() + I[r-1], cmp);
        };
        mergesort(0, I.size());

        int64_t R = INT64_MAX;
        for(auto [t, r] : run)
            if(r < R)
                R = r, dp[m].emplace_back(t, r);
        if(dp[m].size() > 16)
            dp[m].erase(dp[m].begin(), dp[m].end() - 16);
    }

    int64_t result = INT64_MAX;
    for(auto [t, r] : dp[n])
        result = min(result, r);

    cout << result << endl;
}
