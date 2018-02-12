#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 30000;

uint16_t max(uint16_t a, uint16_t b)
{
    return a > b ? a : b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t n;
    cin >> n;
    static array<uint16_t, MAX> A;
    for(uint16_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    uint16_t r = 0;
    for(uint16_t i = 0; i < n - 1; i++)
    {
        uint16_t a = A[i], b = A[i+1];
        uint16_t e = upper_bound(A.begin(), A.begin() + n, a + b) - A.begin();
        r = max(r, e - i);
    }
    cout << r << endl;
}
