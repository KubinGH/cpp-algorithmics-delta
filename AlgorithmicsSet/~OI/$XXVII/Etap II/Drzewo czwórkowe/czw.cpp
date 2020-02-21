#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

constexpr uint Mod = 1e9 + 7;
struct mod_multiplies : multiplies<uint>
{
    uint operator() (uint a, uint b) { return ((uint64_t)a * b) % Mod; }
} Z;

struct quadtree
{
    char type;
    quadtree *child[4];
    size_t id;
};

struct disjoint_set
{
    size_t n;
    vector<size_t> repr, rank;
    vector<uint> val;
    size_t new_node(uint v)
    {
        repr.push_back(repr.size());
        rank.push_back(0);
        val.push_back(v);
        return n++;
    }

    size_t find(size_t u)
    {
        return u == repr[u] ? u : repr[u] = find(repr[u]);
    }

    void unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return;
        if(rank[u] > rank[v])
            swap(u, v);
        if(rank[u] == rank[v])
            rank[v]++;
        repr[u] = v;
    }
} dset;

template<typename It>
quadtree* build_quadtree(It& it, size_t level)
{
    auto t = new quadtree {*it++, 0, 0, 0, 0, SIZE_MAX};
    t->type -= '0';
    if(t->type == 0 or t->type == 1)
        for(size_t i = 0; i < 4; i++)
            t->child[i] = t;
    else if(t->type == 4)
        for(size_t i = 0; i < 4; i++)
            t->child[i] = build_quadtree(it, level - 1);
    else
        abort();
    if(t->type == 1)
        t->id = dset.new_node(level);
    return t;
}

void join_hori(quadtree* w, quadtree* e)
{
    if(w->type == 0 or e->type == 0)
        return;
    else if(w->type == 1 and e->type == 1)
        dset.unite(w->id, e->id);
    else
        join_hori(w->child[1], e->child[0]), join_hori(w->child[3], e->child[2]);
}
void join_vert(quadtree* n, quadtree* s)
{
    if(n->type == 0 or s->type == 0)
        return;
    else if(n->type == 1 and s->type == 1)
        dset.unite(n->id, s->id);
    else
        join_vert(n->child[2], s->child[0]), join_vert(n->child[3], s->child[1]);
}

void join_all(quadtree* t)
{
    if(t->type != 4)
        return;
    join_hori(t->child[0], t->child[1]);
    join_hori(t->child[2], t->child[3]);
    join_vert(t->child[0], t->child[2]);
    join_vert(t->child[1], t->child[3]);
    for(size_t i = 0; i < 4; i++)
        join_all(t->child[i]);
}

void destroy(quadtree* t)
{
    for(size_t i = 0; i < 4; i++)
        if(t != t->child[i])
            destroy(t->child[i]);
    delete t;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint m;
    cin >> m;

    string S;
    cin >> S;
    auto in = S.begin();
    auto root = build_quadtree(in, m);

    join_all(root);

    vector<vector<uint>> lump(dset.n);
    for(size_t i = 0; i < dset.n; i++)
        lump[dset.find(i)].push_back(2*dset.val[i]);

    uint cnt = 0;
    for(size_t i = 0; i < dset.n; i++)
    {
        if(not lump[i].empty())
        {
            cnt++;
            sort(lump[i].begin(), lump[i].end());

            vector<uint> out, nxt;
            while(not lump[i].empty() or not nxt.empty())
            {
                while(not nxt.empty() and (lump[i].empty() or nxt.back() <= lump[i].back()))
                    lump[i].push_back(nxt.back()), nxt.pop_back();
                auto x = lump[i].back(); lump[i].pop_back();
                if(not out.empty() and out.back() == x)
                    out.pop_back(), nxt.push_back(x + 1);
                else
                    out.push_back(x);
            }
            reverse(out.begin(), out.end());
            swap(out, lump[i]);
        }
    }
    uint mx = 0;
    auto opt = *max_element(lump.begin(), lump.end());
    for(auto e : opt)
        mx += power(2, e, Z), mx %= Mod;

    cout << cnt << endl << mx << endl;

    destroy(root);
}
