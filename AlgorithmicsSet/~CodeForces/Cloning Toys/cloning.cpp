#include <bits/stdc++.h>

using namespace std;

int main()
{
    int64_t x, y;
    cin >> x >> y;
    cout << ((x == 0 or y > 1) and x >= y - 1 and (y - x) % 2 ? "Yes" : "No");
}
