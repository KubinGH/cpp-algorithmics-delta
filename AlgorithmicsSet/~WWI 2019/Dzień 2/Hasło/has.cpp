#include <bits/stdc++.h>

using namespace std;

const uint MOD = 1e9 + 7;

template<typename T>
vector<vector<T>> make_vector(size_t w, size_t h, T v = {})
{
    return {w, vector<T>(h, v)};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    string S, Z;
    cin >> S >> Z;

    auto f = [&](pair<int, uint> a, pair<int, uint> b) {
        if(a.first < b.first)
            return a;
        else if(a.first > b.first)
            return b;
        else
            return make_pair(a.first, (a.second + b.second) % MOD);
    };
    auto inc = [&](pair<int, uint> a) {
        return make_pair(a.first + 1, a.second);
    };

    auto R = make_vector<pair<int, uint>>(n+1, m+1, {INT_MAX, 1});

    R[0][0] = {0, 1};
    for(size_t i = 1; i <= n; i++)
        R[i][0] = {i, 1};
    for(size_t j = 1; j <= m; j++)
        R[0][j] = {j, 1};

    for(size_t i = 1; i <= n; i++)
        for(size_t j = 1; j <= m; j++)
    {
        auto& r = R[i][j];
        auto x = R[i-1][j], y = R[i][j-1], z = R[i-1][j-1];
        if(S[i-1] == Z[j-1])
            r = f(r, inc(z));
        else
            r = f(r, inc(f(x, y)));
    }

    cout << R[n][m].second << endl;
}
