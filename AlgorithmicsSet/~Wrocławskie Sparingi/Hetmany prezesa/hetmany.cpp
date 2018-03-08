#include <bits/stdc++.h>

using namespace std;

int64_t max(int64_t a, int64_t b)
{
    return a > b ? a : b;
}
int64_t min(int64_t a, int64_t b)
{
    return a < b ? a : b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int64_t n; uint32_t q;
    cin >> n >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        int64_t x, y;
        cin >> x >> y;
        cout << (1 + // self
                 (n - 1) + // rows
                 (n - 1) + // cols
                 (n - abs(y - x) - 1) + // diagonal down-up
                 (min(n, x + y + 1) - max(0, x + y - n + 1)) - 1) // diagonal up-down
                 << '\n';
    }
}
