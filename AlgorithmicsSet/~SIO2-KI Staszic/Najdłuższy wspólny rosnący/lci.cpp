#include <bits/stdc++.h>

using namespace std;

template<typename T>
constexpr inline T lsb(T x) { return x & (-x); }

template<typename T>
struct max_fenwick_tree
{
    size_t n; T minim;
    vector<T> F;
    max_fenwick_tree(size_t _n, T _minim) : n(_n+1), minim(_minim), F(n+1, minim) {}
    T get_prefix(size_t p) const
        { T r = minim; p++; while(p) r = max(r, F[p]), p -= lsb(p); return r; }
    void set(size_t p, T v)
        { p += 2; while(p <= n) F[p] = max(F[p], v), p += lsb(p); }
};

template<typename T>
struct max_fenwick_tree_2d
{
    size_t w, h; T minim;
    vector<max_fenwick_tree<T>> G;
    max_fenwick_tree_2d(size_t _w, size_t _h, T _minim) :
        w(_w+1), h(_h+1), minim(_minim), G(h+1, max_fenwick_tree<T>(_w, minim)) {}

    T get_prefix(size_t x, size_t y) const
        { T r = minim; y++; while(y) r = max(r, G[y].get_prefix(x)), y -= lsb(y); return r; }
    void set(size_t x, size_t y, T v)
        { y += 2; while(y <= h) G[y].set(x, v), y += lsb(y); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<uint32_t> A(n), B(m);
    unordered_map<uint32_t, vector<uint32_t>> U, V;
    set<uint32_t> Us, Vs;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        U[A[i]].push_back(i); Us.insert(A[i]);
    }
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> B[i];
        V[B[i]].push_back(i); Vs.insert(B[i]);
    }
    vector<uint32_t> K;
    set_intersection(Us.begin(), Us.end(), Vs.begin(), Vs.end(), back_inserter(K));
    Us.clear(); Vs.clear();
    using pair_u16 = pair<uint16_t, uint16_t>;
    using lci_dt = pair<uint16_t, pair_u16>;
    vector<vector<uint16_t>> L(n+1, vector<uint16_t>(m+1));
    vector<vector<pair_u16>> S(n+1, vector<pair_u16>(m+1));
    max_fenwick_tree_2d<lci_dt> F(n+1, m+1, lci_dt(0, {0, 0}));
    vector<pair<pair_u16, lci_dt>> M;
    M.reserve(1<<17);
    for(uint32_t k : K)
    {
        M.clear();
        for(uint32_t u : U[k])
        {
            uint32_t local_best = F.get_prefix(u+1, V[k].back()+1).first;
            bool found_local_best = false;
            for(uint32_t v : V[k])
            {
                tie(L[u+1][v+1], S[u+1][v+1]) = F.get_prefix(u+1, v+1);
                if(L[u+1][v+1] == local_best)
                {
                    if(found_local_best)
                        break;
                    else
                        found_local_best = true;
                }
                L[u+1][v+1]++;
                M.push_back({{u+1, v+1}, {L[u+1][v+1], {u+1, v+1}}});
            }
        }
        for(auto p : M)
            F.set(p.first.first, p.first.second, p.second);
    }
    auto result = F.get_prefix(n+1, m+1);
    auto length = result.first; auto source = result.second;
    cout << length << "\n";
    uint32_t u = source.first, v = source.second;
    stack<uint32_t> R;
    while(u and v)
    {
        R.push(A[u-1]);
        tie(u, v) = S[u][v];
    }
    while(not R.empty())
        cout << R.top() << " ", R.pop();
}
