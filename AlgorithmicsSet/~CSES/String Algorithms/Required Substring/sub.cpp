#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t mod = 1e9 + 7, A = 26;
const char char_lo = 'A', char_hi = 'Z';

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t m;
    cin >> m;

    string S;
    cin >> S;

    const size_t n = S.size();

    vector<size_t> P(n);
    for(size_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[i] != S[P[i]])
            P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]])
            P[i]++;
    }
    vector<vector<size_t>> G(n);

    for(size_t i = 0; i < n; i++)
    {
        for(char c = char_lo; c <= char_hi; c++)
        {
            size_t p = i;
            while(p and c != S[p])
                p = P[p - 1];
            if(c == S[p])
                G[i].push_back(p + 1);
            else
                G[i].push_back(0);
        }
    }

    vector<size_t> V(n+1), W(n+1);
    V[0] = 1;
    while(m --> 0)
    {
        fill(W.begin(), W.end(), 0);
        for(size_t d = 0; d < n; d++)
            for(auto p : G[d])
                W[p] += V[d];
        W[n] += A * V[n];
        for(auto& w : W)
            w %= mod;
        swap(V, W);
    }

    cout << V.back() << endl;
}
