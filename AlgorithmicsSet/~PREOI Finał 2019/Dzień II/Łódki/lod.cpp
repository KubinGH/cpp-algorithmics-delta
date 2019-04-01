#include <bits/stdc++.h>

using namespace std;

const uint32_t MOD = 1e9 + 7;

template<typename T, T Mod>
struct fenwick_tree_dynmod
{
    size_t n;
    map<size_t, T> F;
    static constexpr inline Tp lsb(Tp x) { return x & (-x); }
    fenwick_tree_dynmod(size_t _n) : n(_n) {}
    T get_prefix(size_t p)
    { 
        T r = 0; 
        while(p) 
            r += F[p], r %= Mod, p -= fenwicks::lsb(p); 
        return r; 
    }
    void delta(size_t p, T v)
    { 
        p++; 
        while(p <= n) 
            F[p] += v, F[p] %= Mod, p += fenwicks::lsb(p); 
    }
};


int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 

    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n+1), B(n+1);
    uint32_t m = 0;
    for(uint32_t i = 1; i <= n; i++)
        cin >> A[i] >> B[i], m = max(m, B[i]);
    vector<uint32_t> S(n+1);

    fenwick_tree_dynmod<uint32_t, MOD> F(m+1);
    vector<uint32_t> marks;
    F.delta(0, 1);
    for(uint32_t i = 1; i <= n; i++)
    {
        const uint32_t a = A[i], b = B[i];
        for(uint32_t x = b+1; x --> a; )
        {
            F.delta(x, F.get_prefix(x));
            cerr << i << "/" << x << ": " << F.get_prefix(x) << endl;
        }
    }
    cout << (MOD + F.get_prefix(m+1) - 1) % MOD;
}
