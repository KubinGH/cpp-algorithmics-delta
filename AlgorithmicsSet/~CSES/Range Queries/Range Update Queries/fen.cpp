#include <bits/stdc++.h>
 
using namespace std;
 
template<typename T>
struct fenwick_tree
{
    vector<T> F;
    const size_t n;
 
    fenwick_tree(size_t _n) : F(_n+1), n(_n) {}
 
    template<typename It>
    fenwick_tree(It first, It last) : F(first, last), n(F.size())
    {
        F.insert(F.begin(), 0);
        for(size_t p = 1; p <= n; p++)
            if(p + (p&-p) <= n)
                F[p + (p&-p)] += F[p];
    }
 
    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += p & -p;
    }
 
    T get_prefix(size_t p) const
    {
        T r = 0;
        while(p)
            r += F[p], p &= p - 1;
        return r;
    }
};
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
 
    size_t n, q;
    cin >> n >> q;
 
    vector<int> A(n);
    for(auto& a : A)
        cin >> a;
 
    for(size_t i = A.size(); i --> 1; )
        A[i] -= A[i-1];
    fenwick_tree<int64_t> tree(A.begin(), A.end());
 
    while(q --> 0)
    {
        char t;
        cin >> t;
        if(t == '1')
        {
            size_t l, r; int v;
            cin >> l >> r >> v; l--;
            tree.delta(l, +v);
            tree.delta(r, -v);
        }
        else if(t == '2')
        {
            size_t p;
            cin >> p;
            cout << tree.get_prefix(p) << '\n';
        }
    }
}
