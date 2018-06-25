#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t b, q;
    cin >> b >> q;
    static uint64_t A[MAX];
    uint64_t mod = 0;
    for(uint64_t i = 0; i < b; i++)
    {
        cin >> A[i];
        mod += A[i] * i;
        mod %= b - 1;
    }
    if(mod)
        A[mod]--;
    static uint64_t S[MAX];
    for(uint32_t i = 0; i < b; i++)
        S[i+1] = S[i] + A[i];
    for(uint32_t i = 0; i < q; i++)
    {
        uint64_t k;
        cin >> k;
        uint32_t p = upper_bound(S, S + b+1, k) - S;
        if(p > b)
            cout << -1 << "\n";
        else
            cout << p-1 << "\n";
    }
}
