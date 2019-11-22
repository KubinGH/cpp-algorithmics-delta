#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    set<uint64_t, greater<uint64_t>> basis;
    for(size_t i = 0; i < n; i++)
    {
        uint64_t x;
        cin >> x;

        for(auto y : basis)
            x = min(x, x ^ y);

        if(x)
            basis.insert(x);
    }

    while(q --> 0)
    {
        uint64_t x;
        cin >> x;

        for(auto y : basis)
            x = min(x, x ^ y);

        cout << (x ? "NIE" : "TAK") << '\n';
    }
}
