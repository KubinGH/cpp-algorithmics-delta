#include <bits/stdc++.h>

using namespace std;

const size_t MAX_F = 88;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static array<uint64_t, MAX_F> F;
    F[0] = F[1] = 1;
    for(uint32_t i = 2; i < MAX_F; i++)
        F[i] = F[i-1] + F[i-2];
    uint64_t n; uint32_t k;
    cin >> n >> k;
    static array<uint32_t, MAX_F> C;
    uint32_t p = 0;
    for(uint32_t i = MAX_F; i --> 0; )
    {
        while(F[i] <= n)
        {
            C[i]++; p++;
            n -= F[i];
        }
    }
    if(p > k)
    {
        cout << "NIE";
        return 0;
    }
    for(uint32_t i = MAX_F; p < k and i --> 2;)
    {
        while(p < k and C[i] > 0)
        {
            C[i]--;
            C[i-1]++;
            C[i-2]++;
            p++;
        }
    }
    if(p == k)
        for(uint32_t i = 0; i < MAX_F; i++)
            for(uint32_t c = 0; c < C[i]; c++)
                cout << F[i] << " ";
    else
        cout << "NIE";
}
