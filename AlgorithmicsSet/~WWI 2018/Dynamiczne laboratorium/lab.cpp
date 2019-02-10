#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 11;

struct disjoint_set
{
    uint32_t n;
    vector<uint32_t> parent, rank_of;
    vector<bool> mark;
    disjoint_set(size_t n)
    {
        parent.resize(n); rank_of.resize(n); mark.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    void unite(uint32_t a, uint32_t b)
    {
        if((a = root(a)) == (b = root(b)))
            return;
        if(rank_of[a] > rank_of[b])
            swap(a, b);
        if(rank_of[a] == rank_of[b])
            rank_of[b]++;
        parent[a] = b;
    }
    uint32_t root(uint32_t a) { return parent[a] == a ? a : parent[a] = root(a); }
};

struct rect_t { uint32_t x1, y1, x2, y2; };

rect_t solve_quad(uint32_t v, disjoint_set& dset, uint32_t dx = 0, uint32_t dy = 0)
{
    if(v <= 1)
    {

    }
}

int main()
{
    disjoint_set dset(MAX*MAX);
    solve_quad(2, dset);
    bitset<MAX*MAX> K;
    uint32_t r = 0;
    for(uint32_t i = 0; i < MAX*MAX; i++)
        if(dset.mark[dset.root(i)])
            K[dset.root(i)] = true, r++;
    cout << r;
}
