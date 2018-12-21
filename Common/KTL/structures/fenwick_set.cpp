// Fenwick set. Kind of a self-made idea.
// Operations in O(log n), but the max element (n) must be provided and the memory usage is O(n).
// Also has neat pseudo-iterators.
// It has around the same speed as std::set, but exploiting
// the internal structure is easier
// (e.g. rebinding the left/right pointers helps
//  to get rid of an extra binary search)

// Last revision: December 2018

#include "fenwick.cpp"

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

/*
Example driver
#include <bits/stdc++.h>
using namespace std;
int main()
{
    fenwick_set F(128);
    char c;
    while(cin >> c)
    {
        uint32_t v; cin >> v;
        if(c == '+')
            F.insert(v);
        else if(c == '-')
            F.erase(v);
        else if(c == '^')
            cout << *F.lower_bound(v) << endl;
        else if(c == '>')
            cout << *(++F.find(v)) << endl;
        else if(c == '<')
            cout << *(--F.find(v)) << endl;
    }
}
*/
