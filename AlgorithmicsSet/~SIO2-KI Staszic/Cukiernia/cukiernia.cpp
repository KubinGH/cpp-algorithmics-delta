#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t n, k;
    cin >> n >> k;
    static array<uint32_t, MAX+1> R;
    for(uint32_t ni = 0; ni < n; ni++)
    {
        uint32_t c, s;
        cin >> c >> s;
        for(uint32_t i = k + 1; i --> c;)
            R[i] = max(R[i], R[i - c] + s);
    }
    cout << R[k];
}
