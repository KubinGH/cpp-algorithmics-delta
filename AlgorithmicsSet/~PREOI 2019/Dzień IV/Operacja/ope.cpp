#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

vector<gp_hash_table<uint32_t, null_type>> children;
vector<uint32_t> parent;
vector<bool> active;

uint32_t next_node = 1, reachable = 1;

void initialize()
{
    children.emplace_back();
    parent.push_back(-1u);
    active.push_back(true);
}

void new_conn(uint32_t v)
{
    uint32_t u = next_node++;
    children.emplace_back();
    parent.push_back(-1u);
    active.push_back(false);
    if(not active[v])
        return;
    else
    {
        reachable++;
        children[v].insert(u);
        parent[u] = v;
        active[u] = true;
    }
}

void dfs_cut(uint32_t v)
{
    if(not active[v])
        return;
    for(uint32_t u : children[v])
        dfs_cut(u);
    children[v].clear();
    parent[v] = -1u;
    active[v] = false;
    reachable--;
}

void disconnect(uint32_t v, uint32_t u)
{
    if(parent[v] == u) swap(u, v);
    children[v].erase(u);
    dfs_cut(u);
}

void UmyjRece() { initialize(); }
int Dodaj(int v) { new_conn(v); return reachable; }
int Usun(int v, int u) { disconnect(u, v); return reachable; }
