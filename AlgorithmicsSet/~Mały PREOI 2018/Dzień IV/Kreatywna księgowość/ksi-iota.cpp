#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;


namespace fenwicks
{
    template<typename Tp>
    static constexpr inline Tp lsb(Tp x) { return x & (-x); }
}

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1, 0) {}
    T get_prefix(size_t p) const // Sum in [0, p)
        { T r = 0; while(p) r += F[p], p -= fenwicks::lsb(p); return r; }
    void delta(size_t p, T v)
        { p++; while(p <= n) F[p] += v, p += fenwicks::lsb(p); }

    T get(size_t a, size_t b) const // Get on interval [a, b]
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const // Get on point [p]
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }

    size_t lower_bound(T v)
    {
        // min p: get_prefix(p) >= v
        T s = 0; size_t p = 0;
        for(size_t i = (32 - __builtin_clz(n)); i --> 0; ) // \log2(n)/+1
            if(p + (1u << i) < n and s + F[p + (1u << i)] < v)
                s += F[p + (1u << i)], p += 1u << i;
        return p;
    }
    size_t find_by_order(size_t i) { return lower_bound(i+1) - 1; }
};

struct fenwick_set
{
    size_t n, c = 0;
    fenwick_tree<size_t> F;
    vector<size_t> L, R;
    vector<bool> E;

    // contains elements in range [1, n]
    fenwick_set(size_t _n) : n(_n), F(n+2), L(n+2, -1u), R(n+2, -1u), E(n+2)
    {
        reinitialize();
    }
    void reinitialize()
    {
        F.delta(0, 1); F.delta(n+1, 1);
        R[0] = n+1; L[n+1] = 0;
        E[0] = true; E[n+1] = true;
    }
    void clear()
    {
        fill(F.F.begin(), F.F.end(), 0);
        fill(L.begin(), L.end(), -1u);
        fill(R.begin(), R.end(), -1u);
        fill(E.begin(), E.end(), false);
        reinitialize();
    }
    size_t size() const { return c; }
    size_t basic_lower_bound(size_t v) { return F.lower_bound(F.get_prefix(v) + 1); }
    size_t basic_upper_bound(size_t v) { return basic_lower_bound(v+1); }

    void insert(size_t v)
    {
        if(E[v]) return;
        E[v] = true; c++;
        F.delta(v, 1);
        R[v] = basic_upper_bound(v);
        L[v] = L[R[v]];
        L[R[v]] = v;
        R[L[v]] = v;
    }
    void erase(size_t v)
    {
        if(not E[v]) return;
        E[v] = false; c--;
        F.delta(v, -1u);
        L[R[v]] = L[v];
        R[L[v]] = R[v];
        L[v] = R[v] = -1u;
    }

    struct proxy
    {
        size_t v; const fenwick_set* p;
        proxy() {}
        proxy(size_t _v, const fenwick_set* _p) : v(_v), p(_p) {}
        proxy& operator++ () { v = p->R[v]; return *this; }
        proxy& operator-- () { v = p->L[v]; return *this; }
        size_t operator* () const { return v; }
        bool operator== (const proxy& o) const { return v == o.v and p == o.p; }
        bool operator!= (const proxy& o) const { return not (*this == o); }
    };

    proxy find(size_t v) { return {v, this}; }
    proxy lower_bound(size_t v) { return {basic_lower_bound(v), this}; }
    proxy upper_bound(size_t v) { return {basic_upper_bound(v), this}; }
    proxy begin() { return {basic_lower_bound(1), this}; }
    proxy end() { return {n+1, this}; }
};
struct query_t { uint32_t L, R; bool t; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static int32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t a;
        cin >> a;
        A[i] = a;
    }
    static query_t queries[MAX];
    for(uint32_t i = 0; i < q; i++)
        cin >> queries[i].L >> queries[i].R >> queries[i].t;
    static int32_t E[MAX];
    copy(A, A + n, E);
    sort(E, E + n);
    uint32_t m = unique(E, E + n) - E;
    uint32_t lo = 0, hi = m;
    fenwick_set Q(n+1);
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        //cout << "== " << mid << " ==" << endl;
        Q.clear();
        vector<bool> P(n+2);
        using Qit = fenwick_set::proxy;
        auto Qprint = [&]() {
            for(auto p : Q)
                cout << "<" << p << ": " << P[p] << "> ";
            cout << endl;
        }; (void)Qprint;
        Q.insert(1); P[1] = A[0] > E[mid];
        for(uint32_t i = 1; i < n; i++)
            if((A[i-1] > E[mid]) != (A[i] > E[mid]))
                Q.insert(i+1), P[i+1] = A[i] > E[mid];
        //Qprint();
        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t L = queries[i].L, R = queries[i].R;
            Qit itL = Q.upper_bound(L), itR = Q.upper_bound(R+1); --itL; --itR;
            Q.insert(L); Qit itL1 = Q.find(L); P[L] = P[*itL];
            Q.insert(R+1); Qit itR1 = Q.find(R+1); P[R+1] = P[*itR];
            uint32_t c = 0;
            vector<Qit> to_erase;
            Qit it0, it1;
            for(it0 = it1 = itL1, ++it1; it0 != itR1; ++it0, ++it1)
            {
                to_erase.push_back(it0);
                if(P[*it0])
                    c += *it1 - *it0;
            }
            for(Qit it : to_erase)
                Q.erase(*it);
            bool b = 1;
            if(queries[i].t == 0)
                c = (R - L + 1) - c, b = !b;
            if(c > 0)
                Q.insert(L), P[L] = b;
            if(L+c <= R)
                Q.insert(L+c), P[L+c] = !b;
            //Qprint();
        }
        auto itr = Q.upper_bound(n/2+1); --itr;
        if(P[*itr] == 0)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << E[lo];
}
