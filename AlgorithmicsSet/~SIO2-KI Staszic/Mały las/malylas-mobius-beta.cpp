#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<int8_t> M(n+1);
    M[1] = 1;
    for(uint32_t i = 1; i <= n; i++)
        for(uint32_t x = 2*i; x <= n; x += i)
            M[x] -= M[i];
    int64_t r = 2;
    for(int64_t d = 1; d <= (int64_t)n; d++)
        r += M[d] * (n/d) * (n/d);
    cout << r;
}
