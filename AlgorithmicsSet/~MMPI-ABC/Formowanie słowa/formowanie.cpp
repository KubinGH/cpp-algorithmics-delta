#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    string S;
    cin >> S;
    static array<uint32_t, MAX> R;
    R[0] = 1;
    for(uint32_t i = 1; i < n; i++)
    {
        bool ok = false;
        uint32_t p = 0;
        if(i % 2 == 1)
        {
            ok = true;
            p = (i + 1) / 2;
            for(uint32_t j = 0; j < p; j++)
                if(S[j] != S[p+j])
                    ok = false;
        }
        R[i] = (ok ? R[p - 1] : R[i - 1]) + 1;
    }
    cout << R[n - 1];
}
