#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<array<int, 3>> S(n+1);
    while(m --> 0)
    {
        size_t l, r, k;
        cin >> l >> r >> k; l--; k--;
        S[l][k]++; S[r][k]--;
    }

    for(size_t i = 0; i < n; i++)
        for(size_t k = 0; k < 3; k++)
            S[i+1][k] += S[i][k];

    cout << count_if(S.begin(), S.end(), [&](const auto& v) {
        return v[0] and v[1] and not v[2];
    }) << endl;
}
