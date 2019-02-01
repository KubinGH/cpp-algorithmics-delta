#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; int32_t k;
    cin >> n >> k;
    vector<int32_t> H(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> H[i];
    uint32_t r = 0;
    for(uint32_t t = 0; t < 2; t++)
    {
        int32_t c = 0;
        for(uint32_t i = 0, j = 1; j < n; j++)
        {
            c += max(H[j] - H[j-1], 0);
            while(i < j and c > k)
            {
                c -= max(H[i+1] - H[i], 0);
                i++;
            }
            r = max(r, j - i + 1);
        }
        reverse(H.begin(), H.end());
    }
    cout << r;
}
