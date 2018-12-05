#include <bits/stdc++.h>

using namespace std;

template<typename Iterator>
vector<uint32_t> prefixosuffixes(Iterator S, size_t n)
{
    vector<uint32_t> P(n);
    P[0] = 0;
    for(uint32_t i = 1; i < n; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[P[i]] != S[i]) P[i] = P[P[i] - 1];
        if(S[i] == S[P[i]]) P[i]++;
    }
    return P;
}

template<typename Iterator>
vector<uint32_t> prefixoprefixes(Iterator S, size_t n)
{
    vector<uint32_t> Z(n);
    uint32_t L = 0, R = 0;
    Z[0] = n;
    for(uint32_t i = 1; i < n; i++)
    {
        if(i <= R and Z[i-L] < R-i+1)
            Z[i] = Z[i-L];
        else
        {
            L = i;
            if(i > R) R = i;
            while(R < n and S[R-L] == S[R])
                R++;
            R--;
            Z[i] = R - L + 1;
        }
    }
    return Z;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string S;
    cin >> S;
    const uint32_t n = S.size();
    vector<uint32_t> P = prefixosuffixes(S.begin(), n),
                     Z = prefixoprefixes(S.begin(), n);
    vector<uint32_t> L;
    L.reserve(n); L.push_back(n);
    while(P[L.back()-1])
        L.push_back(P[L.back()-1]);
    reverse(L.begin(), L.end());
    uint32_t lo = 0;
    for(uint32_t x : L)
    {
        if(x < lo)
            continue;
        uint32_t m = 0;
        for(uint32_t i = 0; i+x <= n; i++)
        {
            if(Z[i] >= x)
                m = i+x;
            if(i >= m)
                break;
        }
        if(m >= n)
        {
            lo = x;
            break;
        }
        else
            lo = 2*x;
    }
    cout << lo;
}
