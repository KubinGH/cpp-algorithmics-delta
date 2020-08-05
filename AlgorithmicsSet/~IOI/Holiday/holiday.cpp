#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;

    static constexpr size_t lsb(size_t x) { return x & -x; }

    fenwick_tree(size_t m) : n(m), F(n+1) {}

    T get_prefix(size_t p) const
    {
        T r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }

    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }

    size_t lower_bound(T v)
    {
        if(v == 0) return 0;
        size_t p = 0; T s = 0;
        for(size_t k = __lg(n) + 1; k --> 0; )
            if(p + (1 << k) <= n and s + F[p + (1 << k)] < v)
                s += F[p += (1 << k)];
        return p + 1;
    }
};

struct max_sum_set
{
    vector<int> A;
    vector<size_t> B;
    fenwick_tree<int> cnt;
    fenwick_tree<int64_t> sum;

    max_sum_set(vector<int> a) : A(a), B(A.size()), cnt(A.size()), sum(A.size())
    {
        auto C = B;
        iota(C.begin(), C.end(), 0);
        sort(C.begin(), C.end(), [&](size_t lhs, size_t rhs) {
            return A[lhs] > A[rhs];
        });
        for(size_t i = 0; i < A.size(); i++)
            B[C[i]] = i;
    }

    void push(size_t i)
    {
        if(i >= A.size()) return;
        cnt.delta(B[i], +1);
        sum.delta(B[i], +A[i]);
    }

    void pop(size_t i)
    {
        if(i >= A.size()) return;
        cnt.delta(B[i], -1);
        sum.delta(B[i], -A[i]);
    }

    int64_t get(size_t k)
    {
        return sum.get_prefix(cnt.lower_bound(min(k, (size_t)cnt.get_prefix(A.size()))));
    }
};

void divida_et_impera(
    size_t d1, size_t d2, size_t p1, size_t p2,
    vector<int64_t>& result, max_sum_set& V, const vector<int>& A, int mv)
{
    if(d1 >= d2)
        return;

    size_t d = (d1 + d2) / 2, p = p1;
    int64_t& r = result[d];

    for(size_t i = p1; i < p2 and mv*i <= d; i++)
    {
        auto v = V.get(d-mv*i);
        if(v > r)
            r = v, p = i;
        V.push(i);
    }
    for(size_t i = p1; i < p2 and mv*i <= d; i++)
        V.pop(i);

    divida_et_impera(d1, d, p1, p+1, result, V, A, mv);
    for(size_t i = p1; i < p; i++) V.push(i);
    divida_et_impera(d+1, d2, p, p2, result, V, A, mv);
    for(size_t i = p1; i < p; i++) V.pop(i);
}

vector<int64_t> best_values(vector<int> A, size_t d, int mv = 1)
{
    vector<int64_t> result(d+1);
    max_sum_set V(A);
    divida_et_impera(0, d+1, 0, A.size()+1, result, V, A, mv);
    return result;
}

int64_t solve_right(const vector<int>& A, size_t s, size_t d)
{
    auto R = best_values(vector<int>(A.begin() + s, A.end()), d),
         L = best_values(vector<int>(A.rbegin() + (A.size()-s), A.rend()), d, 2);
    int64_t result = 0;
    for(size_t r = 0; r <= d; r++)
        result = max(result, R[r] + L[d-r]);
    return result;
}

long long int findMaxAttraction(int n, int start, int d, int a[])
{
    vector<int> A(a, a + n);
    int64_t result = solve_right(A, start, d+1);
    reverse(A.begin(), A.end());
    result = max(result, solve_right(A, n-1 - start, d+1));
    return result;
}
