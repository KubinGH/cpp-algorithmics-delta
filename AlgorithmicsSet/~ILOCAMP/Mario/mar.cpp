#include <bits/stdc++.h>

using namespace std;

struct platform
{
    uint32_t a, b, h;
    bool operator< (const platform& o) const
    {
        return tie(h, a, b) < tie(o.h, o.a, o.b);
    }
};

struct segment_tree
{
    constexpr static uint32_t n = 1<<21, w = 1<<20;
    uint32_t assignment[n], ntime[n], mtime = 0;
    segment_tree()
    {
        fill(assignment, assignment + n, -1u);
        fill(ntime, ntime + n, 0);
    }
    void mut(uint32_t getL, uint32_t getR, uint32_t value)
    {
        ++mtime;
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) assignment[getL] = value, ntime[getL] = mtime, getL++;
            if(getR % 2) --getR, assignment[getR] = value, ntime[getR] = mtime;
        }
    }
    uint32_t get(uint32_t p)
    {
        uint32_t r = -1u, t = 0;
        p += w;
        do {
            if(ntime[p] > t)
                t = ntime[p], r = assignment[p];
            p /= 2;
        } while(p);
        return r;
    }
};

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

uint32_t abs_diff(uint32_t a, uint32_t b) { return a>b ? a - b : b - a; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    vector<platform> P(n+1);
    for(uint32_t i = 0; i < n; i++)
        cin >> P[i].a >> P[i].b >> P[i].h;
    P[n].a = 0; P[n].b = (1<<20)-1; P[n].h = 0;
    n++;
    sort(P.begin(), P.end());
    uint32_t X, Y;
    cin >> X >> Y;
    uint32_t id = 0;
    vector<vector<pair<uint32_t, uint32_t>>> C(n); // (x, id)
    vector<vector<pair<uint32_t, uint32_t>>> G(5*n);
    static segment_tree T;
    auto connect = [&](uint32_t p, uint32_t x1, uint32_t d, uint32_t x2) {
        uint32_t r = abs_diff(x1, x2);
        G[p].emplace_back(d, r);
        G[d].emplace_back(p, r);
    };
    auto try_connect_new = [&](uint32_t i, uint32_t j, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
        if(abs_diff(y1, y2) > k)
            return;
        uint32_t p = id++, d = id++;
        C[i].emplace_back(x1, p);
        C[j].emplace_back(x2, d);
        connect(p, x1, d, x2);
    };
    pair<uint32_t, vector<uint32_t>> collect = {0, {}};
    uint32_t start, finish;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t h = P[i].h, a = P[i].a, b = P[i].b;
        if(h > collect.first)
        {
            for(uint32_t j : collect.second)
                T.mut(P[j].a, P[j].b, j);
            collect.first = h;
            collect.second.clear();
        }
        if(i != 0)
        {
            uint32_t fL = T.get(a-1), fR = T.get(b+1);
            if(fL != -1u)
                try_connect_new(i, fL, a, h, a-1, P[fL].h);
            if(fR != -1u)
                try_connect_new(i, fR, b, h, b+1, P[fR].h);
        }
        if(h == 0)
            C[i].emplace_back(0, start = id++);
        if(h == Y and a <= X and X <= b)
            C[i].emplace_back(X, finish = id++);
        collect.second.push_back(i);
    }
    for(uint32_t i = 0; i < n; i++)
    {
        sort(C[i].begin(), C[i].end());
        if(C[i].size() > 1) for(uint32_t j = 0; j < C[i].size()-1; j++)
            connect(C[i][j].second, C[i][j].first, C[i][j+1].second, C[i][j+1].first);
    }

    const uint32_t V = id;
    vector<uint64_t> D(V, -1LLU);
    min_priority_queue<pair<uint64_t, uint32_t>> Q;
    D[start] = 0; Q.emplace(0, start);
    while(not Q.empty())
    {
        auto p = Q.top(); Q.pop();
        uint64_t d; uint32_t u; tie(d, u) = p;
        if(d > D[u]) continue;
        for(auto e : G[u])
        {
            uint64_t w; uint32_t v; tie(v, w) = e;
            if(D[u] + w < D[v])
                Q.emplace(D[v] = D[u] + w, v);
        }
    }
    if(D[finish] == -1LLU)
        cout << "NIE";
    else
        cout << D[finish];
}
