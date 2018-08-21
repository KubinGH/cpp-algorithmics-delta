#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 3e5+16;

pair<uint32_t, uint32_t> bounds[MAX];
set<uint32_t> allow[MAX], range[MAX];
uint32_t vis[MAX], mtime = 1, conn[MAX];

bool match(uint32_t u)
{
    vis[u] = mtime;
    for(uint32_t v : allow[u])
    {
        if(conn[v] == -1u)
        {
            conn[v] = u;
            return true;
        }
    }
    for(uint32_t v : allow[u])
    {
        if(vis[conn[u]] != mtime and match(conn[u]))
        {
            conn[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    for(uint32_t i = 0; i < n; i++)
        bounds[i] = {0, n-1};
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t i, j, a; cin >> i >> j >> a;
        for(uint32_t k = i; k <= j; k++)
            range[a].insert(k);
        uint32_t x, y; tie(x, y) = bounds[a];
        bounds[a] = {max(x, i), min(y, j)};
        if(bounds[a].first > bounds[a].second)
        {
            cout << -1;
            return 0;
        }
    }
    set<uint32_t> disallow;
    for(uint32_t i = n; i --> 0; )
    {
        for(uint32_t x = bounds[i].first; x <= bounds[i].second; x++)
            allow[i].insert(x);
        for(uint32_t x : disallow)
            allow[i].erase(x);
        for(uint32_t x : range[i])
            disallow.insert(x);
    }
    fill(conn, conn + n, -1u);
    bool ok = true;
    for(uint32_t i = 0; i < n; i++)
    {
        bool f = match(i);
        if(not f)
        {
            cout << -1;
            return 0;
        }
        mtime++;
    }
    for(uint32_t i = 0; i < n; i++)
        cout << conn[i] << " ";
}
