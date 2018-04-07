#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 18;

int main()
{
    uint32_t n, w;
    cin >> n >> w;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint32_t r;
    cin >> r;
    static array<bool, MAX> D;
    uint32_t d = n;
    bool ok = true;
    for(uint32_t g = 0; g < r; g++)
    {
        uint32_t k;
        cin >> k;
        uint32_t c = 0;
        for(uint32_t i = 0; i < k; i++)
        {
            uint32_t a;
            cin >> a; a--;
            c += A[a];
            if(c > w or D[a])
            {
                ok = false;
                break;
            }
            else
                D[a] = true, d--;
        }
    }
    if(d)
        ok = false;
    cout << (ok ? "+" : "-");
}
