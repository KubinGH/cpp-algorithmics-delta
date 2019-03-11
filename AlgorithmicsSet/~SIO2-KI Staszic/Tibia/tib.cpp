#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T, typename BinaryOperation = plus<uint32_t>>
struct dynamic_fenwick_tree
{
    size_t n;
    gp_hash_table<size_t, T> F;
    BinaryOperation O;
    dynamic_fenwick_tree(size_t _n) : n(_n) {}
    static constexpr inline size_t lsb(size_t x) { return x & -x; }
    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] = O(F[p], v), p += lsb(p);
    }
    T get_prefix(size_t p)
    {
        T r = 0;
        while(p)
            r = O(r, F[p]), p -= lsb(p);
        return r;
    }
};
struct max_u32 { uint32_t operator() (uint32_t a, uint32_t b) { return max(a, b); } };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;

    vector<tuple<uint32_t, uint32_t, uint32_t>> A(k);
    for(uint32_t i = 0; i < k; i++)
        cin >> get<0>(A[i]) >> get<1>(A[i]) >> get<2>(A[i]);
    dynamic_fenwick_tree<uint32_t, max_u32> F(m+1);
    sort(A.begin(), A.end());
    for(const auto& p : A)
    {
        uint32_t x, y, w;
        tie(x, y, w) = p;
        uint32_t r = F.get_prefix(y+1) + w;
        F.delta(y, r);
    }
    cout << F.get_prefix(m+1);
}
