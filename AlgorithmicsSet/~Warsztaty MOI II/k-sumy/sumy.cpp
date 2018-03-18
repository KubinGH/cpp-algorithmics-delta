#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    int64_t S = 0;
    static array<int64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        S += A[i];
        if(i >= k - 1)
        {
            cout << S << ' ';
            S -= A[i + 1 - k];
        }
    }
}
