#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;

struct query_t { uint32_t L, R; bool t; };

int32_t A[MAX];
query_t queries[MAX];
int32_t E[MAX];

#ifdef _WIN32
#define getchar_unlocked getchar
#endif
struct unlocked_cin
{
    unlocked_cin& operator>> (char& x)
    {
        x = getchar_unlocked();
        return *this;
    }
    unlocked_cin& operator>> (bool& x)
    {
        x = getchar_unlocked() - '0';
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        char lchar; x = 0;
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false; x = 0;
        char lchar;
        if((lchar = getchar_unlocked()) == '-')
            s = true;
        else
            x += lchar - '0';
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        if(s) x = -x;
        return *this;
    }
} ucin;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    size_t lg, qlg;
    fenwick_tree(size_t _n) :
        n(_n), F(n+1, 0),
        lg(32 - __builtin_clz(n)), qlg(1 << (lg-1)) {}
    T get_prefix(size_t p) const // Sum in [0, p)
        { T r = 0; while(p) r += F[p], p &= p - 1; return r; }
    void delta(size_t p, T v)
        { p++; while(p <= n) F[p] += v, p |= p - 1, p++; }

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
        for(size_t i = lg, q = qlg; i --> 0; q /= 2) // \log2(n)/+1
            if(p + q < n and s + F[p + q] < v)
                s += F[p + q], p += q;
        return p;
    }
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
    bool empty() const { return size() == 0; }
    size_t basic_lower_bound(size_t v) { return F.lower_bound(F.get_prefix(v) + 1); }
    size_t basic_upper_bound(size_t v) { return basic_lower_bound(v+1); }

    void basic_insert(size_t v)
    {
        E[v] = true; c++;
        F.delta(v, 1);
    }

    void insert(size_t v)
    {
        if(E[v]) return;
        basic_insert(v);
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

int solve_fenwick_set(uint32_t n, uint32_t q)
{
    //static int32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        ucin >> A[i];
    //static query_t queries[MAX];
    for(uint32_t i = 0; i < q; i++, getchar_unlocked())
        ucin >> queries[i].L >> queries[i].R >> queries[i].t;
    //static int32_t E[MAX];
    copy(A, A + n, E);
    sort(E, E + n);
    uint32_t m = unique(E, E + n) - E;

    fenwick_set Q(n+1);
    uint32_t lo = 0, hi = m;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        Q.clear();
        vector<bool> P(n+2);
        Q.insert(1); P[1] = A[0] > E[mid];
        for(uint32_t i = 1; i < n; i++)
            if((A[i-1] > E[mid]) != (A[i] > E[mid]))
                Q.insert(i+1), P[i+1] = A[i] > E[mid];
        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t L = queries[i].L, R = queries[i].R;
            bool eR = Q.E[R+1];
            Q.insert(R+1);
            if(not eR)
                P[R+1] = P[Q.L[R+1]];
            uint32_t c = 0;
            vector<uint32_t> to_erase;
            uint32_t it0, it1;
            for(it1 = R+1, it0 = Q.L[R+1]; it0 >= L; it1 = it0, it0 = Q.L[it0])
            {
                to_erase.push_back(it0);
                if(P[it0])
                    c += it1 - it0;
            }
            if(P[it0])
                c += it1 - L;
            for(uint32_t it : to_erase)
                Q.erase(it);
            bool b = 1;
            if(queries[i].t == 0)
                c = (R - L + 1) - c, b = !b;
            if(c > 0)
            {
                P[L] = b;
                if(not Q.E[L])
                {
                    Q.basic_insert(L);
                    Q.L[L] = Q.L[R+1]; Q.R[L] = Q.R[Q.L[R+1]];
                    Q.R[Q.L[R+1]] = L; Q.L[Q.R[L]] = L;
                }
            }
            if(L+c <= R)
            {
                P[L+c] = !b;
                if(not Q.E[L+c])
                {
                    Q.basic_insert(L+c);
                    Q.R[L+c] = R+1; Q.L[L+c] = Q.L[R+1];
                    Q.R[Q.L[L+c]] = L+c; Q.L[R+1] = L+c;
                }
            }
        }
        auto itr = Q.upper_bound(n/2+1); --itr;
        if(P[*itr] == 0)
            hi = mid;
        else
            lo = mid+1;
    }
    printf("%d\n", E[lo]);
    return 0;
}


constexpr uint32_t None = 0, Set0 = 2, Set1 = 1;
struct bin_segment_bush
{
    size_t w;
    uint32_t values[MAX], mutate[MAX], nodeL[MAX], nodeR[MAX];
    bin_segment_bush(size_t n)
    {
        w = 1 << (31 - __builtin_clz(2*n-1));
        fill(values, values + 2*w, 0);
        fill(mutate, mutate + 2*w, None);
        for(uint32_t i = 2*w; i --> w; )
            nodeL[i] = nodeR[i] = i - w;
        for(uint32_t i = w; i --> 1; )
            nodeL[i] = nodeL[2*i], nodeR[i] = nodeR[2*i+1];
    }
    void pull(size_t i)
    {
        if(mutate[i] == None) return;
        if(i < w)
            mutate[2*i] = mutate[2*i+1] = mutate[i];
        values[i] = mutate[i] == Set1 ? nodeR[i] - nodeL[i] + 1 : 0;
        mutate[i] = None;
    }
    uint32_t get(size_t i, size_t getL, size_t getR)
    {
        pull(i);
        if(nodeR[i] < getL or nodeL[i] > getR)
            return 0;
        else if(getL <= nodeL[i] and nodeR[i] <= getR)
            return values[i];
        else
            return get(2*i, getL, getR) +
                   get(2*i+1, getL, getR);
    }
    uint32_t get(size_t getL, size_t getR) { return get(1, getL, getR); }
    void mut0(size_t i, size_t getL, size_t getR)
    {
        if(getL <= nodeL[i] and nodeR[i] <= getR)
        {
            if(i < w)
                mutate[2*i] = mutate[2*i+1] = Set0;
            values[i] = 0;
            mutate[i] = None;
        }
        else if(nodeL[i] <= getR and getL <= nodeR[i])
        {
            pull(i);
            mut0(2*i, getL, getR);
            mut0(2*i+1, getL, getR);
            values[i] = values[2*i] + values[2*i+1];
        }
    }
    void mut0(size_t getL, size_t getR) { mut0(1, getL, getR); }
    void mut1(size_t i, size_t getL, size_t getR)
    {
        if(getL <= nodeL[i] and nodeR[i] <= getR)
        {
            if(i < w)
                mutate[2*i] = mutate[2*i+1] = Set1;
            values[i] = nodeR[i] - nodeL[i] + 1;
            mutate[i] = None;
        }
        else if(nodeL[i] <= getR and getL <= nodeR[i])
        {
            pull(i);
            mut1(2*i, getL, getR);
            mut1(2*i+1, getL, getR);
            values[i] = values[2*i] + values[2*i+1];
        }
    }
    void mut1(size_t getL, size_t getR) { mut1(1, getL, getR); }
};

int solve_segment_tree(uint32_t n, uint32_t q)
{
    //static int32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        ucin >> A[i];
    //static query_t queries[MAX];
    uint32_t qsum = 0;
    for(uint32_t i = 0; i < q; i++, getchar_unlocked())
    {
        ucin >> queries[i].L >> queries[i].R >> queries[i].t;
        queries[i].L--; queries[i].R--;
        uint32_t d = queries[i].R - queries[i].L + 1;
        qsum += d * (31 - __builtin_clz(d));
    }
    if(qsum < (1<<20))
    {
        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t L = queries[i].L, R = queries[i].R + 1;
            if(queries[i].t == 0)
                sort(A + L, A + R);
            else
                sort(A + L, A + R, greater<int32_t>());
        }
        printf("%d\n", A[n/2]);
        return 0;
    }
    //static int32_t E[MAX];
    copy(A, A + n, E);
    sort(E, E + n);
    //uint32_t m = unique(E, E + n) - E;
    uint32_t lo = 0, hi = n;
    static bin_segment_bush T(n);
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        for(uint32_t i = n; i --> 0; )
            T.values[T.w + i] = A[i] > E[mid], T.mutate[T.w + i] = None;
        for(uint32_t i = T.w; i --> 1; )
            T.values[i] = T.values[2*i] + T.values[2*i+1], T.mutate[i] = None;
        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t L = queries[i].L, R = queries[i].R;
            uint32_t c = T.get(L, R);
            if(queries[i].t)
                T.mut1(L, L+c-1), T.mut0(L+c, R);
            else
                T.mut0(L, R-c), T.mut1(R-c+1, R);
        }
        if(T.get(n/2, n/2) == 0)
            hi = mid;
        else
            lo = mid+1;
    }
    printf("%d\n", E[lo]);
    return 0;
}


int main()
{
    uint64_t n, q;
    ucin >> n >> q;
    if(n * q <= uint64_t(1e7))
        solve_segment_tree(n, q);
    else
        solve_fenwick_set(n, q);
}
