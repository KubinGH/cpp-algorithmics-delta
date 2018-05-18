#include <bits/stdc++.h>

using namespace std;

bool R(uint32_t x)
{
    return x == 4 or not (x%2 or __builtin_popcount(x) == 1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t x;
        cin >> x;
        cout << (R(x) ? "TAK\n" : "NIE\n");
    }
}
