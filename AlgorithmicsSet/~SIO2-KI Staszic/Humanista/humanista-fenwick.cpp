#include <bits/stdc++.h>

using namespace std;

template<typename T, typename BinaryOperation = plus<T>>
struct fenwick_tree
{
    static inline size_t lsb(size_t x) { return x & -x; }
    uint32_t n;
    vector<T> F;
    BinaryOperation op;
    fenwick_tree(uint32_t _n, BinaryOperation _op = {}) : n(_n), F(n+1), op(_op) {}
    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] = op(F[p], v), p += lsb(p);
    }
    T get_prefix(size_t p)
    {
        T r = 0;
        while(p)
            r = op(r, F[p]), p -= lsb(p);
        return r;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    fenwick_tree<uint32_t, bit_xor<uint32_t>> F(n);
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        F.delta(i, A[i]);
    }
    while(q --> 0)
    {
        string c; uint32_t a, b;
        cin >> c >> a >> b; a--; b--;
        if(c == "czytaj")
            cout << (F.get_prefix(b+1) ^ F.get_prefix(a)) << "\n";
        else if(c == "zamien")
        {
            F.delta(a, A[a]^A[b]);
            F.delta(b, A[a]^A[b]);
            swap(A[a], A[b]);
        }
    }
}
