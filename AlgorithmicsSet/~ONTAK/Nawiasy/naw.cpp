#include <bits/stdc++.h>

using namespace std;

const uint64_t oo = UINT64_MAX / 3;
const size_t NAX = 256;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

size_t f(char c)
{
    switch(c)
    {
        case '(': return 0; case ')': return 1;
        case '[': return 2; case ']': return 3;
        case '{': return 4; case '}': return 5;
        case '<': return 6; case '>': return 7;
    }
    return 8;
}

int main()
{
    size_t n, m, s, t;
    cin >> n >> m >> s >> t; s--; t--;

    static vector<size_t> in[NAX][8], out[NAX][8];
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; char c;
        cin >> u >> v >> c; u--; v--;
         in[v][f(c)].push_back(u);
        out[u][f(c)].push_back(v);
    }

    static uint64_t L[NAX][NAX];
    for(size_t u = 0; u < n; u++)
        for(size_t v = 0; v < n; v++)
            L[u][v] = +oo;

    min_priority_queue<pair<uint64_t, pair<size_t, size_t>>> Q;
    auto maybe = [&](size_t u, size_t v, uint64_t d) {
        if(d < L[u][v])
            Q.emplace(L[u][v] = d, make_pair(u, v));
    };
    for(size_t u = 0; u < n; u++)
        maybe(u, u, 0);

    static bool lock[NAX][NAX];
    while(not Q.empty())
    {
        auto u = Q.top().second.first, v = Q.top().second.second; Q.pop();
        if(lock[u][v])
            continue;
        lock[u][v] = true;

        for(size_t k = 0; k < 4; k++)
            for(auto u1 : in[u][2*k])
                for(auto v1 : out[v][2*k+1])
                    maybe(u1, v1, L[u][v] + 2);

        for(size_t w = 0; w < n; w++)
        {
            maybe(u, w, L[u][v] + L[v][w]);
            maybe(w, v, L[w][u] + L[u][v]);
        }
    }

    if(L[s][t] == +oo)
        cout << "-1" << endl;
    else
        cout << L[s][t] << endl;
}
