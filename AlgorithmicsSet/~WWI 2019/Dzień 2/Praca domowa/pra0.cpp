#include <bits/stdc++.h>

using namespace std;

const uint MOD = 1e9 + 7;

vector<size_t> prefixosuffixes(const string& S)
{
    const size_t n = S.size();
    vector<size_t> P(n);
    P[0] = 0;
    for(size_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[P[i]] != S[i])
            P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]])
            P[i]++;
    }
    return P;
}

vector<size_t> matching_shifts(string S, string Z)
{
    const size_t n = S.size();

    vector<size_t> T; T.reserve(n);

    auto pat = S + "#" + Z + Z;
    auto patpat = prefixosuffixes(pat);

    const size_t patset = 2*n;
    for(size_t i = 0; i < n; i++)
        if(patpat[i + patset] == n)
            T.push_back(i);

    return T;
}

uint mod_mul(uint a, uint b)
{
    return (uint64_t)a * b % MOD;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;

    cin >> n >> k;

    vector<uint> W(n);
    W[0] = 1;
    uint sigma = 1;

    vector<uint> wh = {1};

    for(size_t e = 0; e < k; e++)
    {
        for(size_t i = 0; i < n; i++)
            W[i] = (MOD + sigma - W[i]) % MOD;

        sigma = mod_mul(sigma, n - 1);

        wh.push_back(W[0]);
    }

    for(size_t e = 0; e + 4 < k; e++)
    {
        assert((MOD + wh[e+3] - wh[e+1]) % MOD == mod_mul(n - 1, MOD + wh[e+2] - wh[e]));
    }

    cout << W[0];

/*
    string S, Z;
    cin >> S >> Z;

    uint result = 0;
    for(auto t : matching_shifts(S, Z))
        result += W[t];

    cout << result << '\n';
*/
}
