#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; uint64_t k;
    cin >> n >> k;
    static array<uint64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(A[i] % k != 0)
            i--, n--;
    }
    sort(A.begin(), A.begin() + n);
    uint64_t v = k;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i] != v)
        {
            cout << v;
            return 0;
        }
        v += k;
    }
    cout << k * (n + 1);
}
