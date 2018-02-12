#include <bits/stdc++.h>
#define C(i, j) (C0[j] - C0[i] - (DS[j] - DS[i]) * WS[i])

using namespace std;

const size_t MAX = 20000;

int main()
{
    uint16_t n;
    cin >> n;
    static array<uint64_t, MAX> W, D;
    static array<uint64_t, MAX+1> WS, DS, C0;
    for(uint16_t i = 0; i < n; i++)
    {
        cin >> W[i] >> D[i];
        if(i > 0) { WS[i+1] = WS[i]; DS[i+1] = DS[i]; C0[i+1] = C0[i]; }
        WS[i+1] += W[i]; DS[i+1] += D[i];
        C0[i+1] += WS[i+1] * D[i];
    }
    uint64_t result = numeric_limits<uint64_t>::max();
    pair<uint16_t, uint16_t> r;
    for(uint16_t i = 0; i < n; i++)
    {
        for(uint16_t j = i+1; j < n; j++)
        {
            uint64_t v = C(0, i) + C(i+1, j) + C(j+1, n);
            cout << i << " : " << j << " -> " << v << endl;
            result = min(result, v);
            if(v == result)
                r = make_pair(i, j);
        }
    }
    cout << result << endl;
    cout << r.first << " " << r.second << endl;
}
