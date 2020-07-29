#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<tuple<uint, size_t, size_t>> T(m);
    for(auto& [c, a, b] : T)
        cin >> a >> b >> c;

    sort(T.begin(), T.end());

    static uint dp[4096][64][64];
    static pair<uint16_t, uint16_t> opt[4096][64][64];
    // dp[k][i][j] - best value considering
    //               only intervals with index >= k and inside [i, j]

    static uint16_t cnt[64][64][64];
    // cnt[i][j][t] - count of intervals with index >= k containing t inside [i, j]

    for(size_t k = m; k --> 0; )
    {
        for(size_t t = get<1>(T[k]); t <= get<2>(T[k]); t++)
            for(size_t i = 1; i <= get<1>(T[k]); i++)
                for(size_t j = get<2>(T[k]); j <= n; j++)
                    cnt[i][j][t]++;

        for(size_t i = 1; i <= n; i++)
        {
            for(size_t j = i; j <= n; j++)
            {
                if(k == m-1) opt[k][i][j] = {i, m-1};
                else         opt[k][i][j] = opt[k+1][i][j], dp[k][i][j] = dp[k+1][i][j];
                for(size_t t = i; t <= j; t++) // point of placement t
                {
                    auto r = dp[k+1][i][t-1] + dp[k+1][t+1][j] + get<0>(T[k])*cnt[i][j][t];
                    if(r > dp[k][i][j])
                        dp[k][i][j] = r, opt[k][i][j] = {t, k};
                }
            }
        }
    }

    cout << dp[0][1][n] << endl;

    vector<uint> val(n+1, get<0>(T.back()));
    function<void(size_t, size_t, size_t)> solve = [&](size_t k, size_t i, size_t j) {
        if(i > j or k >= m) return;
        auto [t, l] = opt[k][i][j];
        val[t] = get<0>(T[l]);
        solve(l+1, i, t-1);
        solve(l+1, t+1, j);
    };
    solve(0, 1, n);
    for(size_t i = 1; i <= n; i++)
        cout << val[i] << ' ';
    cout << endl;
}
