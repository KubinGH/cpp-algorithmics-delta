#include <bits/stdc++.h>

using namespace std;

vector<uint32_t> prefixosuffixes(const vector<uint32_t>& S)
{
    const uint32_t n = S.size();
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

vector<bool> period_set(const vector<uint32_t>& S)
{
    const uint32_t n = S.size();
    vector<bool> R(n + 1);
    vector<uint32_t> P = prefixosuffixes(S);
    uint32_t p = n;
    while(p) p = P[p - 1], R[n-p] = true;
    return R;
}

vector<uint32_t> prefixoprefixes(const vector<uint32_t>& S)
{
    const uint32_t n = S.size();
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

// period of form A .. ~A
vector<bool> antiperiod_set(const vector<uint32_t>& S, const vector<bool>& R)
{
    const uint32_t n = S.size();
    vector<bool> L(n + 1);
    vector<uint32_t> T(2*n+1); T[n] = 2;
    for(uint32_t i = 0; i < n; i++) T[i] = S[i];
    for(uint32_t i = 0; i < n; i++) T[i+(n+1)] = S[i] ^ 1;
    vector<uint32_t> Z = prefixoprefixes(T);
    for(uint32_t k = 1; k <= n/2; k++)
        L[k] = R[2*k] and Z[k+(n+1)] >= k;
    for(uint32_t k = n/2+1; k <= n; k++)
        L[k] = Z[k+(n+1)] >= min(k, n-k);
    return L;
}

pair<vector<bool>, vector<bool>> get_lengths(const vector<uint32_t>& A)
{
    const uint32_t n = A.size();
    vector<uint32_t> S(n+1);
    for(uint32_t i = 0; i < n; i++)
        S[i+1] = (S[i] ^ A[i]) & 1;
    vector<bool> R = period_set(S), L = antiperiod_set(S, R);
    vector<bool> V(n+1), W(n+1); V[0] = W[0] = true;
    for(uint32_t k = 1; k <= n; k++)
    {
        if(R[k])
            W[k] = true, V[k] = false;
        else if(L[k])
            W[k] = false, V[k] = true;
        else
            W[k] = true, V[k] = true;
    }
    return {V, W};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t n, m;
        cin >> n >> m;
        vector<uint32_t> A(n), B(m);
        for(uint32_t i = 0; i < n; i++) cin >> A[i];
        for(uint32_t i = 0; i < m; i++) cin >> B[i];
        vector<bool> VA, VB, WA, WB;
        tie(VA, WA) = get_lengths(A);
        tie(VB, WB) = get_lengths(B);
        for(uint32_t k = min(n, m)+1; k --> 0; )
            if((VA[k] and VB[k]) or (WA[k] and WB[k]))
                { cout << k << "\n"; break; }
    }
}

