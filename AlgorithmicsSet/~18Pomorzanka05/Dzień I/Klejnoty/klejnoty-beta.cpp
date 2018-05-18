#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    //static uint32_t parent[MAX];
    static vector<uint32_t> children[MAX];
    stack<uint32_t> to_vis;
    vector<uint32_t> topo;
    static bitset<MAX> vis;
    to_vis.push(0); vis[0] = true;
    while(not to_vis.empty())
    {
        uint32_t u = to_vis.top(); to_vis.pop();
        topo.push_back(u);
        for(uint32_t v : graph[u])
        {
            if(not vis[v])
            {
                vis[v] = true;
                to_vis.push(v);
                children[u].push_back(v);
                //parent[v] = u;
            }
        }
    }
    reverse(topo.begin(), topo.end());
    static vector<uint32_t> R[MAX];
    for(uint32_t u : topo)
    {
        R[u].reserve(n);
        for(uint32_t p = 0; p < 13; p++)
        {
            R[u].push_back(p);
            for(uint32_t v : children[u])
            {
                uint32_t c = -1u;
                for(uint32_t vp = 0; vp < 13; vp++)
                {
                    if(p == vp)
                        continue;
                    c = min(c, R[v][vp]);
                }
                R[u][p] += c;
                if(p == 12)
                    R[v].clear(), R[v].shrink_to_fit();
            }
        }
    }
    uint32_t r = -1u;
    for(uint32_t p = 0; p < 13; p++)
        r = min(r, R[topo.back()][p]);
    cout << r + n;
}
