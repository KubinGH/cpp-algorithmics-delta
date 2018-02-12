#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t t;
    cin >> t;
    for(uint16_t ti = 0; ti < t; ti++)
    {
        uint16_t n, p;
        cin >> n >> p;
        static array<uint32_t, MAX> B;
        fill(B.begin(), B.end(), 0);
        for(uint16_t ni = 0; ni < n; ni++)
        {
            uint16_t w; uint32_t v;
            cin >> w >> v;
            for(uint16_t i = p + 1; i --> w;)
                if(B[i-w] + v > B[i])
                    B[i] = B[i-w] + v;
        }
        cout << B[p] << '\n';
    }
}
