#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    static array<uint32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], S[i+1] = S[i] + A[i];
    vector<uint32_t> R;
    for(uint32_t c = 1; c <= S[n]; c++)
    {
        bool ok = true;
        for(uint32_t i = 0; i < n;)
        {
            uint32_t j = lower_bound(S.begin(), S.begin() + n + 1, S[i] + c) - S.begin();
            if(S[j] - S[i] != c)
            {
                ok = false;
                break;
            }
            else
                i = j;
        }
        if(ok)
            cout << c << " ";
    }
}
