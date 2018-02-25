#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;
const size_t MAX_T = 21, MAX_A = 79;
const uint32_t INF = 1 << 30;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t, a, n;
    cin >> t >> a >> n;
    static array<array<uint32_t, MAX_A+1>, MAX_T+1> M;
    for(uint32_t i = 0; i <= t; i++)
        M[i].fill(INF);
    M[0][0] = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t vt, va, vm;
        cin >> vt >> va >> vm;
        for(uint32_t it = t + vt + 1; it --> vt;)
        {
            for(uint32_t ia = a + va + 1; ia --> va;)
            {
                M[min(t,it)][min(a,ia)] = min(M[min(t,it)][min(a,ia)], M[it-vt][ia-va] + vm);
            }
        }
    }
    cout << M[t][a];
}
