#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 7000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], A[i] *= A[i];
    sort(A.begin(), A.begin() + n);
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = i+1; j < n; j++)
        {
            uint64_t c = A[i]+A[j];
            auto it = lower_bound(A.begin(), A.begin() + n, c);
            if(it == A.begin() + n or *it != c)
                continue;
            auto it2 = upper_bound(it, A.begin() + n, c);
            r += distance(it, it2);
        }
    }
    cout << r;
}
