#include <bits/stdc++.h>

using namespace std;

int64_t f(int y, int x)
{
    const auto z = max(x, y), c = 2*z + 1, i1 = (y < x ? y : 2*z - x);
    const auto i = z%2 ? i1 : c - i1 - 1;
    return (int64_t)z*z + i;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        size_t y, x;
        cin >> y >> x;

        cout << f(y - 1, x - 1)+1 << '\n';
    }
}
