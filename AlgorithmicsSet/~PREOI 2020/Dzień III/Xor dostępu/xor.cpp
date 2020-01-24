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

        vector<uint64_t> A(n);
        uint64_t s = 0;
        for(size_t i = 0; i < n; i++)
            cin >> A[i], s ^= A[i];

        set<uint64_t, greater<uint64_t>> basis;
        for(auto& x : A)
        {
            x &= s;
            for(auto y : basis)
                x = min(x, x ^ y);
            if(x)
                basis.insert(x);
        }

        if(s == 0)
        {
            cout << 0 << endl;
            continue;
        }

        basis.erase(0);
        vector<uint64_t> vbasis(basis.begin(), basis.end());
        auto m = basis.size();

        uint64_t x = 0;
        size_t p = SIZE_MAX;
        for(size_t i = 0; i < m; i++)
        {
            if(vbasis[i] and __lg(vbasis[i]) == __lg(s))
            {
                x ^= vbasis[i];
                p = i+1;
                break;
            }
        }

        for(size_t i = p; i < m; i++)
            x = min(x, x ^ vbasis[i]);

        cout << (x - (s ^ x)) << endl;
    }
}
