#include <bits/stdc++.h>

using namespace std;

template<typename T, typename ChildrenOp>
struct segment_tree
{
    vector<T> values;
    size_t w;
    ChildrenOp F;
    segment_tree(size_t n, ChildrenOp f = {})
    {
        F = move(f);
        w = 1 << __lg(2*n-1);
        values.resize(2*w, identity_element(F));
    }
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value; i /= 2;
        while(i) values[i] = F(values[2*i], values[2*i+1]), i /= 2;
    }
    T get(size_t getL, size_t getR)
    {
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
};

struct max_u32 { uint32_t operator() (uint32_t a, uint32_t b) { return a>b ? a : b; } };
uint32_t identity_element(max_u32) { return 0; }

struct fenwick_tree
{
    uint32_t n;
    vector<uint32_t> F;
    fenwick_tree(uint32_t _n) : n(_n), F(n+1) {}
    void delta(uint32_t p, uint32_t v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += (p & -p);
    }
    uint32_t get_prefix(uint32_t p) const
    {
        uint32_t r = 0;
        while(p)
            r += F[p], p -= (p & -p);
        return r;
    }
};

using pair_u32 = pair<uint32_t, uint32_t>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<pair_u32> B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].first, B[i].second = i;
    sort(B.begin(), B.end());
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        A[B[i].second] = i;
    segment_tree<uint32_t, max_u32> X_T(n);
    vector<uint32_t> X(n);
    vector<pair<uint32_t, uint32_t>> XX;
    for(uint32_t i = 0; i < n; i++)
    {
        X[i] = X_T.get(A[i]+1, n-1);
        X_T.set(A[i], i+1);
        XX.emplace_back(X[i], i);
    }
    sort(XX.begin(), XX.end());
    vector<tuple<uint32_t, uint32_t, uint32_t>> Q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--;
        Q.emplace_back(a, b, i);
    }
    fenwick_tree F(n);
    vector<uint32_t> result(n);
    sort(Q.begin(), Q.end());
    for(uint32_t qi = 0, xi = 0; qi < q; qi++)
    {
        while(xi < n and XX[xi].first <= get<0>(Q[qi]))
            F.delta(XX[xi].second, 1), xi++;
        result[get<2>(Q[qi])] = F.get_prefix(get<1>(Q[qi])) - F.get_prefix(get<0>(Q[qi]));
    }
    for(uint32_t i = 0; i < q; i++)
        cout << result[i] << "\n";
}
