#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100;
const size_t MAX_W = 10001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX_W> R, W;
    static array<bool, MAX_W> A;
    for(uint32_t i = 1; i < MAX_W; i++)
        R[i] = numeric_limits<uint16_t>::max();
    for(uint32_t it = 0; it < n; it++)
    {
        uint32_t w;
        cin >> w;
        if(A[w]) continue;
        A[w] = true;
        W[it] = w;
        for(uint32_t i = w; i < MAX_W+1; i++)
            R[i] = min(R[i], R[i-w]+1);
    }
    sort(W.begin(), W.begin() + n, greater<uint32_t>());
    uint32_t q;
    cin >> q;
    for(uint32_t it = 0; it < q; it++)
    {
        uint32_t x;
        cin >> x;
        if(R[x] != numeric_limits<uint16_t>::max())
        {
            cout << R[x] << " ";
            uint32_t y = x;
            for(uint32_t r = R[y]+1; r --> 0;)
            {
                for(uint32_t i = 0; i < n; i++)
                {
                    if(y >= W[i] and R[y - W[i]] == r - 1)
                    {
                        y -= W[i];
                        cout << W[i] << " ";
                        break;
                    }
                }
            }
            cout << '\n';
        }
        else
            cout << -1 << '\n';
    }
}
