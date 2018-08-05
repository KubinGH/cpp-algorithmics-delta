#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

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
    static int64_t A[MAX];
    for(uint32_t i = 0; i < n; i++) cin >> A[i];
    static bitset<MAX> vis; vis[0] = true;
    stack<uint32_t> tovis; tovis.push(0);
    static vector<uint32_t> children[MAX];
    vector<uint32_t> topo;
    while(not tovis.empty())
    {
        uint32_t u = tovis.top(); tovis.pop();
        topo.push_back(u);
        for(uint32_t v : graph[u])
        {
            if(not vis[v])
            {
                vis[v] = true;
                tovis.push(v);
                children[u].push_back(v);
            }
        }
    }
    reverse(topo.begin(), topo.end());
    static int64_t D[MAX][2]; // (+1, -1)
    for(uint32_t u : topo)
    {
        D[u][0] = D[u][1] = 0;
        for(uint32_t v : children[u])
            D[u][0] = max(D[u][0], D[v][0]),
            D[u][1] = max(D[u][1], D[v][1]);
        int64_t a = A[u] + D[u][0] - D[u][1];
        D[u][a > 0] += abs(a);
    }
    cout << D[topo.back()][0] + D[topo.back()][1];
}
