#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 24;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static char S[MAX];
    cin >> S;
    S[n] = '#';
    cin >> (S+n+1);
    static uint32_t P[MAX];
    P[0] = 0;
    uint32_t r = 0;
    for(uint32_t i = 1; i <= n+m; i++)
    {
        P[i] = P[i-1];
        while(P[i] and S[i] != S[P[i]])
            P[i] = P[P[i]-1];
        if(S[i] == S[P[i]])
            P[i]++;
        if(P[i] == n and i > n)
            cout << i-2*n+1 << "\n";
    }
}
