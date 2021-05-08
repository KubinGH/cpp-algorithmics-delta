#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        size_t n;
        cin >> n;

        uint r = 0;
        while(n --> 0)
        {
            uint x;
            cin >> x;
            r ^= x;
        }

        cout << (r ? "first" : "second") << '\n';
    }
}
