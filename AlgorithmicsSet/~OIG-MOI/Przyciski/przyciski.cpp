#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<uint32_t, MAX> A;
    uint32_t r = 0, x = 0;
    for(uint32_t mi = 0; mi < m; mi++)
    {
        uint32_t i;
        cin >> i; i--;
        if(i == n)
            r = x;
        else
        {
            A[i] = max(A[i], r) + 1;
            x = max(x, A[i]);
        }
    }
    for(uint32_t i = 0; i < n; i++)
        cout << max(A[i], r) << " ";
}
