#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int k;
    cin >> k;

    const int b = 30, n = 3 * b + 2;

    cout << n << '\n';

    for(size_t i = 0; i < b; i++)
    {
        cout << 3*i+2 << ' ' << (k >> i & 1 ? n : -1) << '\n'; // 3i + 1
        cout << 3*i+3 << ' ' << 3*i+4 << '\n'; // 3i + 2
        cout << 3*i+4 << ' ' << -1 << '\n'; // 3i + 3
    }
    cout << "-1 -1\n-1 -1" << endl;
}
