#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; uint64_t w;
    cin >> n >> w;
    static array<uint64_t, MAX> A;
    static array<uint64_t, MAX+1> S;
    static array<uint32_t, MAX> R;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        S[i+1] = S[i] + A[i];
        if(S[i+1] >= w)
        {
            uint32_t j = upper_bound(S.begin(), S.begin()+i+1, S[i+1] - w)
                         - S.begin() - 1;
            if(j > i)
                j = i;
            uint32_t v = j > 0 ? R[j-1] + 1 : 1;
            if(i > 0)
                R[i] = max(R[i-1], v);
            else
                R[i] = v;
        }
        else if(i > 0)
            R[i] = R[i-1];
    }
    cout << R[n-1];
}
