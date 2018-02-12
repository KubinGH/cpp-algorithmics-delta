#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    uint32_t s = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        s += A[i];
    }
    sort(A.begin(), A.begin() + n);
    for(uint32_t i = 0; i < n / 2; i++)
    {
        s += A[n-i-1] - A[i];
    }
    cout << s;
}
