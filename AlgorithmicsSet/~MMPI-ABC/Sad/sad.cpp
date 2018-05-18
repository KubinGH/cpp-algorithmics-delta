#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t C[1 << 19];
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        r += C[(1<<18) + a - i];
        C[(1<<18) + a - i]++;
    }
    cout << r;
}
