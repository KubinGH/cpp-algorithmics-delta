#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 50;
const size_t MAX_K = 20001;

int main()
{
    uint16_t n, k;
    cin >> n >> k;
    static array<uint32_t, MAX> A;
    for(uint16_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    static array<uint32_t, MAX_K> B;
    for(uint16_t p = 0; p < n; p++)
        for(uint16_t i = k; i >= A[p]; i--)
            B[i] = max(B[i], B[i - A[p]] + 1);
    cout << B[k];
}
