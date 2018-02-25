#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        A[i] = max(i > 0 ? A[i-1] : 0, a);
    }
    uint32_t c = n;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t h;
        cin >> h;
        uint32_t r = distance(A.begin(), upper_bound(A.begin(), A.begin() + c, h - 1));
        c = r - 1;
        cout << r << " ";
    }
}
