#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }

    T get_prefix(size_t p) const
    {
        T r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }

    size_t lower_bound(T v) const 
    {
        size_t p = 0;
        T s = 0;
        for(size_t k = __lg(n)+1; k --> 0; )
            if(p + (1 << k) <= n and s + F[p + (1 << k)] <= v)
                s += F[p + (1 << k)], p += (1 << k);
        return p;
    }
};

int64_t solve_to_right(vector<int64_t> A, int64_t nn, int64_t h)
{
    const size_t n = A.size();
    for(auto& x : A)
        x = (x + h - 1) / h;
    int64_t result = 0, mm = 0;
    for(size_t a = 0, b = 0; a < n; a++)
    {
        while(b < n and mm + A[b] <= nn)
            mm += A[b], b++;
        result = max(result, int64_t(b - a));
        mm -= A[a];
    }
    return result + nn + 1; 
}

struct keeper
{
    const vector<int64_t>& A;
    const vector<size_t>& order;

    int64_t n1, h1, n2, h2, floors = 0, k = 0;
    fenwick_tree<int> occ;
    fenwick_tree<int64_t> ceils;

    keeper(const vector<int64_t>& _A, const vector<size_t>& _order,
           int64_t m1, int64_t g1, int64_t m2, int64_t g2) 
        : A(_A), order(_order), n1(m1), h1(g1), n2(m2), h2(g2), occ(A.size()), ceils(A.size()) {}

    void push(size_t i)
    {
        k++;
        floors += A[i] / h2;
        occ.delta(order[i], 1);
        ceils.delta(order[i], (A[i]%h2 + h1 - 1) / h1);
    }

    void pop(size_t i)
    {
        k--;
        floors -= A[i] / h2;
        occ.delta(order[i], -1);
        ceils.delta(order[i], -((A[i]%h2 + h1 - 1) / h1));
    }

    bool ok() const
    {
        auto m1 = n1, m2 = n2;
        m2 -= floors;
        if(m2 < 0)
            m1 += m2 * (h2 / h1), m2 = 0;
        if(k <= m2)
            m2 -= k;
        else
            m1 -= ceils.get_prefix(occ.lower_bound(size_t(k - m2))), m2 = 0;
        return m1 >= 0 and m2 >= 0;
    }
};

int64_t solve_to_right(vector<int64_t> A, int64_t n1, int64_t h1, int64_t n2, int64_t h2)
{
    if(h1 == h2)
        return solve_to_right(A, n1 + n2, h1);
    const size_t n = A.size();

    vector<pair<int64_t, size_t>> I;
    for(size_t i = 0; i < n; i++)
        I.emplace_back(A[i]%h2, i);
    sort(I.begin(), I.end());
    vector<size_t> order(n);
    for(size_t i = 0; i < n; i++)
        order[I[i].second] = i;

    int64_t result = 0;

    keeper keep(A, order, n1, h1, n2, h2);        
    for(size_t a = 0, b = 0; a < n; a++)
    {
        while(b < n and keep.ok())
            keep.push(b++);
        if(not keep.ok())
            keep.pop(--b);
        result = max(result, int64_t(b - a));
        if(a == b)
            b++;
        else if(a < b)
            keep.pop(a);   
    }

    return result + n1 + n2 + 1;
}

int64_t solve(vector<pair<int64_t, int64_t>> I, int64_t n1, int64_t h1, int64_t n2, int64_t h2)
{
    const size_t n = I.size();

    vector<int64_t> A;

    auto [lastL, lastR] = I[0];
    lastR += lastL;

    for(size_t i = 1; i < n; i++)
    {
        auto [L, R] = I[i];
        R += L;

        if(L <= lastR)
            A.push_back(0), lastR = max(lastR, R);
        else
            A.push_back(L - lastR), lastL = L, lastR = R;
    }    

    return solve_to_right(A, n1, h1, n2, h2);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<int64_t, int64_t>> I(n), J(n);
    for(size_t i = 0; i < n; i++)
    {
        cin >> I[i].first >> I[i].second;
        J[n-i-1] = {-I[i].first, I[i].second};
    }
    
    int64_t n1, h1, n2, h2;
    cin >> n1 >> h1 >> n2 >> h2;

    if(h1 > h2)
        swap(n1, n2), swap(h1, h2);

    cout << max(solve(I, n1, h1, n2, h2), solve(J, n1, h1, n2, h2));
}