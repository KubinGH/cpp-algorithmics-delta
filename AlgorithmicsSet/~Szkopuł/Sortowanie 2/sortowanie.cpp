#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 50000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<int32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.begin() + n);
    for(uint32_t i = 0; i < n; i++)
        cout << A[i] << " ";
}
