#include <bits/stdc++.h>
#include <ktl/math/factorization.cpp>

using namespace std;

int main()
{
    size_t q;
    cin >> q;

    while(q --> 0)
    {
        uint n;
        cin >> n;
        uint r = 1;
        for(auto& [p, e] : _pair_compress(factorize_int(n)))
            r *= e + 1;
        cout << r << '\n';
    }
}
