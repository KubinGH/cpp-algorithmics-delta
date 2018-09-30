#include <bits/stdc++.h>

using namespace std;

template<typename T>
constexpr inline T lsb(T x) { return x & (-x); }

template<typename T>
struct fenwick_tree
{
    size_t n;
    T* F;
    fenwick_tree(size_t _n) { n = _n+1; F = new T[n]; fill(F, F + n, 0); }
    ~fenwick_tree() { delete[] F; }
    T get_prefix(size_t p) const
        { T r = 0; p++; while(p) r += F[p], p -= lsb(p); return r; }
    void delta(size_t p, T v)
        { p += 2; while(p <= n) F[p] += v, p += lsb(p); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q; string s_start;
    cin >> n >> q >> s_start;
    vector<bool> start(n);
    for(uint32_t i = 0; i < n; i++) start[i] = (s_start[i] == 'o');
    fenwick_tree<int32_t> F(n+1);
    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == 'Q')
        {
            uint32_t a; cin >> a; a--;
            cout << ((start[a] ^ F.get_prefix(a+1))&1 ? "ON" : "OFF") << "\n";
        }
        else if(c == 'S')
        {
            uint32_t a, b; cin >> a >> b; a--; b--;
            F.delta(a, 1); F.delta(b+1, -1);
        }
    }
}
