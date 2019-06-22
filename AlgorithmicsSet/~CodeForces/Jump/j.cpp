#include <bits/stdc++.h>

using namespace std;

struct bits_generator
{
    mt19937 gen;
    uint32_t acc = 0, left = 0;
    bool operator() ()
    {
        if(not left)
            left = 32, acc = gen();
        bool o = acc & 1;
        acc >>= 1; left--;
        return o;
    }
};


#ifdef XHOVA
string __M;
int query(const vector<bool>& S)
{
    size_t r = 0;
    cerr << "? ";
    for(size_t i = 0; i < S.size(); i++)
    {
        cerr << S[i];
        if(__M[i] - '0' == S[i])
            r++;
    }
    cerr << endl;
    cerr << "= " << r << endl;
    return r == S.size() ? 2 : (r == S.size()/2);
}
#else
int query(const vector<bool>& S)
{
    for(bool o : S)
        cout << o;
    cout << endl;
    size_t r;
    cin >> r;
    return r == S.size() ? 2 : (r == S.size()/2);
}
#endif

struct disjoint_set
{
    size_t n;
    vector<size_t> parent, nrank;
    disjoint_set(size_t _n) : n(_n)
    {
        parent.resize(n); nrank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    void unite(size_t u, size_t v)
    {
        if(nrank[v = find(v)] > nrank[u = find(u)])
            swap(u, v);
        if(u == v)
            return;
        parent[v] = u;
        if(nrank[u] == nrank[v])
            nrank[u]++;
    }
    size_t find(size_t u)
    {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
#ifdef XHOVA
    //cin >> __M;
    cin >> n;
    __M.resize(n, '1');
#else
    cin >> n;
#endif
    bits_generator bit;
    bit.gen.seed(time(0));
    vector<bool> S(n);

    while(true)
    {
        for(size_t i = 1; i < n; i++)
            S[i] = bit();
        auto r = query(S);
        if(r == 1)
            break;
        else if(r == 2)
            return 0;
    }

    disjoint_set dset(n);
    S[0] = not S[0];
    for(size_t i = 1; i < n; i++)
    {
        S[i] = not S[i];
        auto r = query(S);
        if(r == 2)
            return 0;
        else if(r == 0)
            dset.unite(0, i);
        S[i] = not S[i];
    }
    S[0] = not S[0];

    auto Z1 = S;
    for(size_t i = 0; i < n; i++)
        if(dset.find(i) == dset.find(0))
            Z1[i] = not Z1[i];

    if(query(Z1) == 2)
        return 0;

    auto Z2 = Z1;
    for(size_t i = 0; i < n; i++)
        Z2[i] = not Z2[i];

    if(query(Z2) == 2)
        return 0;

    abort();
}
