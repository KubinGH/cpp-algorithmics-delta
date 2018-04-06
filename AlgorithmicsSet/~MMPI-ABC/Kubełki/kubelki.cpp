#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static array<uint32_t, MAX> A;
    uint32_t s = 0, r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(i >= k+1)
            s -= A[i-k-1];
        cin >> A[i];
        s += A[i];
        r = max(r, s);
    }
    cout << r;
}
