#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

static array<uint32_t, MAX> parent, children_count, subtree_size;
static array<unordered_set<uint32_t>, MAX> children;
static bitset<MAX> removed;

void destructive_dfs(uint32_t u)
{
    for(uint32_t v : children[u])
        if((subtree_size[v] + 1) % 2 == 0)
            destructive_dfs(v);
    cout << u+1 << "\n";
    removed[u] = true;
    for(uint32_t v : children[u])
        if(not removed[v])
            destructive_dfs(v);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    if(n % 2 == 0)
    {
        cout << "NO";
        return 0;
    }
    else
        cout << "YES\n";
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
    uint32_t root = 0;
    for(uint32_t u = 0; u < n; u++)
    {
        if(graph[u].size() == 1)
        {
            root = u;
            break;
        }
    }
    parent[root] = root;
    stack<uint32_t> to_visit;
    vector<uint32_t> topological;
    topological.push_back(root);
    static bitset<MAX> visited;
    to_visit.push(root); visited[root] = true;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        for(uint32_t v : graph[u])
        {
            if(not visited[v])
            {
                topological.push_back(v);
                parent[v] = u;
                to_visit.push(v);
                visited[v] = true;
                children[u].insert(v);
            }
        }
    }
    reverse(topological.begin(), topological.end());
    for(uint32_t u : topological)
    {
        if(parent[u] != u)
            subtree_size[parent[u]] += subtree_size[u] + 1;
    }
    destructive_dfs(root);
    for(uint32_t u = 0; u < n; u++)
        if(not removed[u])
            cout << u+1 << endl;
}
