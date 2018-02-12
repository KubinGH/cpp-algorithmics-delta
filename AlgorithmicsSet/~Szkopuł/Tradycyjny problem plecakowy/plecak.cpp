#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 501;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t n, k;
    cin >> n >> k;
    static array<uint64_t, MAX> B;
    for(uint16_t ni = 0; ni < n; ni++)
    {
        uint16_t w; uint64_t v;
        cin >> w >> v;
        for(uint16_t i = k+1; i --> w;)
            B[i] = max(B[i], B[i-w]+v);
    }
    cout << B[k];
}
