#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<uint32_t>, MAX> graph;
    static array<uint32_t, MAX> incoming;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        incoming[v]++;
    }
    static array<uint32_t, MAX> topological; uint32_t ti = 0;
    uint32_t added = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(incoming[i] == 0)
        {
            topological[ti++] = i;
            added++;
        }
    }
    if(added != 1)
        goto fail;
    for(uint32_t i = 0; i < ti; i++)
    {
        uint32_t u = topological[i];
        added = 0;
        for(uint32_t v : graph[u])
        {
            incoming[v]--;
            if(incoming[v] == 0)
            {
                topological[ti++] = v;
                added++;
            }
        }
        if(added > 1)
            goto fail;
    }
    if(ti < n)
        goto fail;
    cout << "TAK\n";
    for(uint32_t i = 0; i < n; i++)
        cout << topological[i]+1 << " ";
    return 0;
fail:
    cout << "NIE";
}
