#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1u << 17,  MAX_A = 1u << 18, MAX_MEX = 1 << 7;

template<size_t N>
uint32_t mex(bitset<N>& V)
{
    for(uint32_t i = 0; i < N; i++)
        if(not V[i])
            return i;
    return N;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static uint32_t G[MAX_A];
    G[0] = 0;
    uint32_t m = 0;
    for(uint32_t a = 1; a < MAX_A; a++)
    {
        bitset<MAX_MEX> X;
        for(uint32_t q = 1; q * q <= a; q++)
            X[G[a - q*q]] = true;
        G[a] = mex(X);
        X.reset();
        m = max(m, G[a]);
    }
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t n;
        cin >> n;
        uint32_t w = 0;
        for(uint32_t i = 0, a; i < n; i++)
            cin >> a, w ^= G[a];
        cout << (w ? "TAK\n" : "NIE\n");
    }
}
