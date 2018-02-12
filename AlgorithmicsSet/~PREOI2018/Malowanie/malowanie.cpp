#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10000;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint64_t, MAX> C;
    for(uint32_t i = 0; i < n; i++)
        cin >> C[i];
    static array<array<uint64_t, MAX>, MAX> R;
    for(uint32_t i = 0; i < n; i++)
        R[0][i] = C[0];
    for(uint32_t i = 1; i < n; i++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            R[i][x] = min(C[i] + R[i-1][1], R[i-1][x+1] + x);
        }
    }
    uint64_t r = -1;
    for(uint32_t i = 0; i < n; i++)
    {
        r = min(r, R[n-1][i]);
    }
    cout << r;
}
