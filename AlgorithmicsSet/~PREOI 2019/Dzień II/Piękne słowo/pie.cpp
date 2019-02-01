#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> prefixosuffixes(string S)
{
    const uint32_t n = S.size();
    vector<uint32_t> P(n);
    for(uint32_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[i] != S[P[i]])
            P[i] = P[P[i]-1];
        if(S[i] == S[P[i]])
            P[i]++;
    }
    return P;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    string S;
    cin >> S;

    auto P = prefixosuffixes(S);

    using qu64 = uint64_t;
    for(uint32_t d = 1; d <= n; d++)
        cout << (qu64(P[d-1]) * qu64(k) >= qu64(d) * qu64(k - 1));
}
