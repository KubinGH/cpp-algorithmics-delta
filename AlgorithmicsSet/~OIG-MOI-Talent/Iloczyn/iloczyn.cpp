#include <bits/stdc++.h>

using namespace std;

const size_t MAX_M = 256;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    uint32_t Q = ceil(sqrt(n))+1;
    vector<int64_t> A(n);
    vector<vector<int64_t>> S(MAX_M, vector<int64_t>(Q+1, 1));
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        for(uint32_t m = 1; m < MAX_M; m++)
            S[m][i/Q] *= A[i], S[m][i/Q] %= m;
    }
    while(q --> 0)
    {
        uint32_t x, y; int64_t m;
        cin >> x >> y >> m; x--; y--;
        int64_t r = 1;
        for(uint32_t i = x; i <= y; i++)
        {
            if((i % Q) == 0 and i+Q <= y)
                r *= S[m][i/Q], i += Q - 1;
            else
                r *= A[i];
            r %= m;
        }
        cout << r << "\n";
    }
}
