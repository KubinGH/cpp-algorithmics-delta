#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        int a, b;
        cin >> a >> b;

        cout << (2*a >= b and 2*b >= a
          and (2*a - b) % 3 == 0 and (2*a - b) % 3 == 0 ? "YES" : "NO") << '\n';
    }
}
