#include <bits/stdc++.h>
#include <ext/numeric>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t m;
    mod_multiplies(uint64_t _m) : m(_m) {}
    uint64_t operator() (uint64_t a, uint64_t b) { return (a*b) % m; }
};
using namespace __gnu_cxx;
using namespace __gnu_pbds;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t a, b, p;
    while(cin >> a >> b >> p)
    {
        if(a == b)
        {
            if(a == 1) cout << "0\n";
            else cout << "1\n";
            continue;
        }
        mod_multiplies M(p);
        uint32_t r = ceil(sqrt(p));
        gp_hash_table<uint32_t, uint32_t> H;
        uint32_t f = 1;
        H[1] = 0;
        for(uint32_t j = 1; j <= 2*r; j++)
            H[f = M(f, a)] = j;
        uint32_t ar = power(a, p - 1 - r, M), A = 1;
        uint32_t K = -1u;
        for(uint32_t i = 0; i <= 2*r; i++, A = M(A, ar))
        {
            uint32_t B = M(b, A);
            auto itA = H.find(B);
            if(itA != H.end())
            {
                uint32_t j = itA->second;
                uint32_t k = (r*i + j) % (p-1);
                K = min(k, K);
            }
        }
        cout << int(K) << endl;
    }
}
