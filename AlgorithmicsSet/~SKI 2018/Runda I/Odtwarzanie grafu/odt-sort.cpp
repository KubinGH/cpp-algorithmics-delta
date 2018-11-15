#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint64_t nup = uint64_t(n)*uint64_t(n+1)/2;
    vector<pair<uint32_t, uint32_t>> E; E.reserve(n);
    vector<uint32_t> T; T.reserve(n);
    static uint32_t D[MAX]; static uint64_t S[MAX];
    for(uint32_t i = 1; i <= n; i++)
    {
        uint64_t d, s;
        cin >> d >> s;
        if(s > nup) { cout << "NIEMOZLIWE"; return 0; }
        if(d > (uint64_t)n) { cout << "NIEMOZLIWE"; return 0; }
        D[i] = d; S[i] = s;
        if(D[i] == 1)
            T.push_back(i);
    }
    for(uint32_t i = 0; i < T.size(); i++)
    {
        uint32_t t = T[i];
        if(not D[t] or not (1 <= S[t] and S[t] <= n) or S[t] == t) continue;
        E.emplace_back(t, S[t]);
        S[S[t]] -= t;
        D[S[t]]--;
        if(D[S[t]] == 1)
            T.push_back(S[t]);
        D[t]--; S[t] -= S[t];
    }
    for(uint32_t i = 1; i <= n; i++)
    {
        if(D[i] or S[i]) { cout << "NIEMOZLIWE"; return 0; }
    }
    cout << "OK\n";
    cout << E.size() << "\n";
    for(uint32_t i = 0; i < E.size(); i++)
        if(E[i].first > E[i].second) swap(E[i].first, E[i].second);
    sort(E.begin(), E.end());
    for(auto e : E)
        cout << e.first << " " << e.second << "\n";
}
