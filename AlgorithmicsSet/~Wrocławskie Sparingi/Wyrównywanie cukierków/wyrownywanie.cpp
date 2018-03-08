#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

uint32_t absdiff(uint32_t a, uint32_t b)
{
    return a > b ? a - b : b - a;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    uint32_t m = n % 2 ? A[n/2] : (A[n/2] + A[n/2-1])/2;
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
        r += absdiff(A[i], m);
    cout << r;
}
