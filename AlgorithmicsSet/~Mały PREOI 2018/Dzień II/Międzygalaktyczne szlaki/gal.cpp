#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1 << 20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, s;
    cin >> n >> s;
    if(s == 0) { cout << 0; return 0; }
    s--;
    static vector<uint32_t> G[MAX_N];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto bfs = [&](uint32_t st) {
        queue<uint32_t> Q;
        vector<uint32_t> D(n, -1u), P(n, -1u), T;
        T.reserve(n);
        Q.push(st); D[st] = 0;
        while(not Q.empty())
        {
            uint32_t u = Q.front(); Q.pop();
            T.push_back(u);
            for(uint32_t v : G[u])
                if(D[v] == -1u)
                    Q.push(v), D[v] = D[u]+1, P[v] = u;
        }
        return make_tuple(D, P, T);
    };
    auto bfs0 = bfs(0);
    uint32_t root = max_element(get<0>(bfs0).begin(), get<0>(bfs0).end()) - get<0>(bfs0).begin();
    vector<uint32_t> D, P, T;
    tie(D, P, T) = bfs(root);
    uint32_t diend = max_element(D.begin(), D.end()) - D.begin();
    uint32_t diameter_size = 0;
    vector<bool> is_diameter(n);
    {
        uint32_t u = diend;
        do {
            is_diameter[u] = true;
            diameter_size++;
            u = P[u];
        } while(u != -1u);
    }
    reverse(T.begin(), T.end());
    vector<uint32_t> paths, best(n); paths.reserve(2*s);
    for(uint32_t u : T)
    {
        if(is_diameter[u])
        {
            for(uint32_t v : G[u]) if(v != P[u] and not is_diameter[v])
                paths.push_back(best[v]);
        }
        else
        {
            for(uint32_t v : G[u]) if(v != P[u])
            {
                if(best[v] > best[u])
                {
                    if(best[u] > 0)
                        paths.push_back(best[u]);
                    best[u] = best[v];
                }
                else
                    paths.push_back(best[v]);
            }
            best[u]++;
        }
    }
    while(paths.size() < 2*s) paths.push_back(0);
    sort(paths.rbegin(), paths.rend());
    while(paths.size() > 2*s) paths.pop_back();
    cout << accumulate(paths.begin(), paths.end(), 0) + diameter_size;
}
