#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20, MAX_E = 1 << 22;
const size_t E_BITS = 22;

uint32_t neg(uint32_t x) { return x ^ (MAX_E - 1); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX], I[MAX_E], F[MAX_E];
    fill(I, I + MAX_E, -1u); fill(F, F + MAX_E, -1u);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(I[A[i]] == -1u)
            I[A[i]] = i;
    }
    for(uint32_t i = 0; i < MAX_E; i++)
        F[i] = I[i];
    for(uint32_t i = 0; i < E_BITS; i++)
    {
        for(uint32_t a = 0; a < MAX_E; a++)
        {
            if((a & (1 << i)) and F[a] == -1u)
                F[a] = F[a ^ (1 << i)];
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t f = F[neg(A[i])];
        if(f != -1u)
            cout << A[f] << " ";
        else
            cout << "-1 ";
    }
}
