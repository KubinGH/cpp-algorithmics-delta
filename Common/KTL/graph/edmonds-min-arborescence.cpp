// Edmonds minimal arborescence algorithm.
// Finds the weight of the arborescence.
// Last revision: March 2019.

#pragma once

#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <tuple>
#include <stack>
#include <set>

using namespace std;

namespace edmonds
{
    using weight_t = int32_t;

    template<typename Metadata, typename MergeMetadata>
    struct disjoint_set
    {
        MergeMetadata md_merge;
        vector<size_t> repr, deg;
        vector<Metadata> metadata;
        disjoint_set(size_t n) : repr(n), deg(n), metadata(n)
        {
            iota(repr.begin(), repr.end(), 0);
        }
        size_t find(size_t v)
            { return repr[v] == v ? v : repr[v] = find(repr[v]); }
        void unite(size_t u, size_t v)
        {
            u = find(u); v = find(v);
            if(u == v)                  return;
            if(deg[u] > deg[v])         swap(u, v);
            else if(deg[u] == deg[v])   deg[v]++;
            repr[u] = v;
            md_merge(metadata[u], metadata[v]);
        }
        Metadata& get_metadata(size_t v) { return metadata[find(v)]; }
    };

    struct edge
    {
        uint32_t u, v;
        weight_t w;
        edge() : u(0), v(0), w(0) {}
        edge(uint32_t _u, uint32_t _v, weight_t _w)
            : u(_u), v(_v), w(_w) {}
    };
    bool operator< (const edge& a, const edge& b)
        { return make_tuple(a.w, a.u, a.v) < make_tuple(b.w, b.u, b.v); }
    using graph = vector<vector<edge>>;

    template<typename T, typename To>
    struct offsetset { To offset; set<T> S; };

    struct merge_edgy_offsetset
    {
        void operator() (offsetset<edge, weight_t>& src, offsetset<edge, weight_t>& dst)
        {
            if(src.S.size() < dst.S.size())
                for(auto e : src.S)
                    dst.S.emplace(e.u, e.v, e.w + src.offset - dst.offset);
            else
            {
                for(auto e : dst.S)
                    src.S.emplace(e.u, e.v, e.w + dst.offset - src.offset);
                dst.S.swap(src.S);
                dst.offset = src.offset;
            }
            src.offset = 0; src.S.clear();
        }
    };

    // Returns the weight of the minimal arborescence,
    // such that there is a path from every vertex to the root.
    weight_t min_arborescence(const graph& G, size_t root)
    {
        const uint32_t n = G.size();
        disjoint_set<offsetset<edge, weight_t>, merge_edgy_offsetset> D(n);

        for(uint32_t u = 0; u < n; u++) if(u != root)
        {
            auto& md = D.metadata[u].S;
            copy(G[u].begin(), G[u].end(), inserter(md, md.end()));
        }

        vector<bool> stk(n), vis(n), lock(n);

        vis[root] = true;
        weight_t result = 0;

        for(uint32_t s1 = 0; s1 < n; s1++)
        {
            uint32_t s = D.find(s1);
            if(vis[s])
                continue;
            stack<uint32_t> T;
            T.push(s);
            while(not T.empty())
            {
                uint32_t u = T.top();
                stk[u] = vis[u] = true;
                if(D.get_metadata(u).S.empty())
                {
                    T.pop();
                    stk[u] = false;
                    continue;
                }
                auto e = *D.get_metadata(u).S.begin();
                auto w = e.w + D.get_metadata(u).offset;
                uint32_t v = D.find(e.v);
                if(not lock[u])
                {
                    result += w;
                    lock[u] = true;
                }
                if(stk[v])
                {
                    D.get_metadata(v).offset = -D.get_metadata(v).S.begin()->w;
                    do {
                        D.get_metadata(u).offset = -D.get_metadata(u).S.begin()->w;
                        D.unite(v, u);
                        stk[u] = false;
                        T.pop();
                        u = T.top();
                    } while(u != v);

                    stk[v] = false;
                    T.pop();

                    edge e1;
                    auto& md = D.get_metadata(u);
                    while(true)
                    {
                        e1 = *md.S.begin();
                        if(D.find(e1.u) == D.find(e1.v))
                            md.S.erase(md.S.begin());
                        else
                            break;
                    }
                    stk[D.find(u)] = true;
                    vis[D.find(u)] = false;
                    lock[D.find(u)] = false;
                    T.push(D.find(u));
                }
                else if(not vis[v])
                    T.push(v);
                else
                    stk[u] = false, T.pop();
            }
        }

        return result;
    }
}
