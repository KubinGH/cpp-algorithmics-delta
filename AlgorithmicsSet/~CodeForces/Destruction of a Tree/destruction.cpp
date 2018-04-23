#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<vector<uint32_t>, MAX> graph;
    for(uint32_t u = 0; u < n; u++)
    {
        uint32_t v;
        cin >> v; v--;
        if(v != -1u)
        {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }
    stack<uint32_t> to_visit;
    static bitset<MAX> visited;
    static array<uint32_t, MAX> parent, topological;
    static array<unordered_set<uint32_t>, MAX> children;
    uint32_t ti = 0; topological[ti++] = 0;
    to_visit.push(0); visited[0] = true;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        for(uint32_t v : graph[u])
        {
            if(not visited[v])
            {
                parent[v] = u;
                to_visit.push(v);
                visited[v] = true;
                children[u].insert(v);
                topological[ti++] = v;
            }
        }
    }
    reverse(topological.begin(), topological.begin() + n);
    static array<uint32_t, MAX> order; uint32_t oi = 0;
    static bitset<MAX> removed;
    for(uint32_t i = 0, u = topological[0]; i < n; i++, u = topological[i])
    {
        uint32_t p = parent[u];
        if(p != u and (children[p].size() + (parent[p] != p)) % 2 == 0)
        {
            order[oi++] = p;
            removed[p] = true;
            children[parent[p]].erase(p);
            parent[p] = p;
            for(uint32_t c : children[p])
                parent[c] = c;
            children[p].clear();
        }
        if(parent[u] == u and not removed[u])
        {
            if(children[u].size() % 2 == 0)
            {
                removed[u] = true;
                order[oi++] = u;
                for(uint32_t c : children[u])
                    parent[c] = c;
                children[u].clear();
            }
            else
                goto fail;
        }
    }
    cout << "YES\n";
    for(uint32_t i = 0; i < oi; i++)
        cout << order[i]+1 << "\n";
    for(uint32_t i = 0; i < n; i++)
        if(not removed[i])
            cout << i+1 << "\n";
    return 0;
fail:
    cout << "NO";
}
