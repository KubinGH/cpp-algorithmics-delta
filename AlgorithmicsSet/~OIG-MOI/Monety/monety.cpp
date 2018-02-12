#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const uint32_t LIM = 1000000007;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    uint64_t r = 1, b = 0, c = 0;
    uint32_t j = n - 1;
    for(uint32_t i = n + 1; i --> 1; c++)
    {
        while(j != -1u and A[j] >= i)
            j--, b++;
        r *= b - c; r %= LIM;
    }
    cout << r;
}
