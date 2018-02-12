#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 300000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, n;
    cin >> h >> n;
    static array<uint64_t, MAX> R, M;
    for(uint32_t i = 0; i < h; i++)
    {
        cin >> R[i];
        if(i == 0) M[i] = R[i];
        else M[i] = min(M[i - 1], R[i]);
    }
    reverse(M.begin(), M.begin() + h);
    uint32_t b = 0, p = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t r;
        cin >> r;
        p = lower_bound(M.begin() + b, M.begin() + h, r) - M.begin();
        if(p > h) { p = h; break; };
        b = p + 1;
    }
    cout << h - p << endl;
}
