#include <bits/stdc++.h>
#include <ext/numeric>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using __gnu_cxx::power;
using namespace __gnu_pbds;

template<typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag,
         tree_order_statistics_node_update
>;

mt19937_64 gen;
uint64_t randint(uint64_t lo, uint64_t hi)
{
    return uniform_int_distribution<uint64_t>{lo, hi}(gen);
}
const uint64_t P = (1LLU<<61) - 1;
uint64_t M(uint64_t x)
{
    x = (x >> 61) + (x & P);
    return __builtin_expect(x != P, true) ? x : 0;
}
struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator()(uint64_t a, uint64_t b)
    {
        a = M(a); b = M(b);
        uint64_t q = (long double)(a) * b / P;
        int64_t r = (int64_t)(a * b - q * P) % (int64_t)P;
        return r < 0 ? r + P : r;
    }
} Mm;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    gen.seed(42);
    uint32_t n, m;
    cin >> n >> m;
    if(m == 1) { cout << (uint64_t)n*(n+1)/2; return 0; }
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], A[i]--;
    vector<uint64_t> G(m);
    uint64_t g = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        G[i] = randint(0, P-1);
        g = M(g + G[i]);
    }
    uint64_t gT = power(g, P - 2, Mm);
    vector<uint64_t> E(n+1);
    for(uint32_t k = 1; k <= n; k++)
        E[k] = Mm(g, k);

    vector<uint64_t> H(n+1), h(n+1);
    indexed_set<pair<uint64_t, uint32_t>> O;
    
    for(uint32_t i = 0; i < n; i++)
    {
        h[i+1] = M(h[i] + G[A[i]]);
        H[i+1] = Mm(h[i+1], gT);
        O.insert({H[i+1], i});
    }
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        pair<uint64_t, uint32_t>
            L = {H[i] + 1, 0}, R = {H[i]+((n-i)/m), -1u};
        r += O.order_of_key(R) - O.order_of_key(L);
    }
    cout << r;
}
