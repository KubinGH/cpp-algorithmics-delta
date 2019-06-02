#include <bits/stdc++.h>

using namespace std;

struct disjoint_set
{
    size_t n;
    vector<size_t> parent, nrank;
    disjoint_set(size_t _n) : n(_n)
    {
        parent.resize(n); nrank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    bool unite(size_t u, size_t v)
    {
        if(nrank[v = find(v)] > nrank[u = find(u)])
            swap(u, v);
        if(u == v)
            return false;
        parent[v] = u;
        if(nrank[u] == nrank[v])
            nrank[u]++;
        return true;
    }
    size_t find(size_t u)
    {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
};

enum Dir { Horizontal, Vertical };
struct wall { Dir t; size_t x, y; };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t h, w;
    cin >> h >> w;
    vector<wall> walls[2];
    walls[0].reserve(w*h); walls[1].reserve(w*h);
    size_t cc = 0;
    for(size_t y = 0; y < h; y++)
      for(size_t x = 0; x < w - 1; x++)
    {
        char c; cin >> c;
        walls[c == 'C'].push_back({Horizontal, x, y});
        cc += c == 'C';
    }
    for(size_t y = 0; y < h - 1; y++)
      for(size_t x = 0; x < w; x++)
    {
        char c; cin >> c;
        walls[c == 'C'].push_back({Vertical, x, y});
        cc += c == 'C';
    }

    vector<string> output[2];
    output[0].resize(h, string(w - 1, 'Z'));
    output[1].resize(h - 1, string(w, 'Z'));

    disjoint_set dset(w*h);
    size_t total = 0, opt = 0;
    for(size_t c = 0; c < 2; c++)
      for(auto o : walls[c])
    {
        size_t x = o.x, y = o.y;
        if(o.t == Horizontal and dset.unite(y*w+x, y*w+(x+1)))
            output[0][y][x] = '.', total++, opt += c;
        else if(o.t == Vertical and dset.unite(y*w+x, (y+1)*w+x))
            output[1][y][x] = '.', total++, opt += c;
    }

    size_t f = 2*w*h-w-h;
    cout << f-total << " " << cc-opt << endl;
    for(size_t t = 0; t < 2; t++)
        for(size_t y = 0; y < h - t; y++)
            cout << output[t][y] << '\n';
}
