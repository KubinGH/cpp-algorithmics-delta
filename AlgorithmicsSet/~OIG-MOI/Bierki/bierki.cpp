#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 30000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A, P;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    for(uint32_t i = 0; i < n - 1; i++)
        P[i] = A[i] + A[i+1];
    uint32_t r = 0, j = 0;
    for(uint32_t i = 2; i < n; i++)
    {
        while(j != n - 2 and P[j+1] <= A[i]) j++;
        r = max(r, i - j);
    }
    cout << r << endl;
}
