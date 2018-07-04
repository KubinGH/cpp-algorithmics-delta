#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5+16;

inline uint32_t gcd(uint32_t a, uint32_t b) { return __gcd(a, b); }

uint32_t n;
uint32_t A[MAX];
vector<uint32_t> graph[MAX];

uint32_t mtime = 0;
uint32_t parent[MAX];
vector<uint32_t> children[MAX];
uint32_t subtree[MAX];
bitset<MAX> locked;
bool initial_rooting = true;

void root_in_vertex(uint32_t root, map<uint32_t, uint64_t>& pathnums)
{
    stack<uint32_t> to_visit;
    static uint32_t visited[MAX];
    if(initial_rooting)
    {
        for(uint32_t i = 0; i < MAX; i++)
            visited[i] = -1u;
        initial_rooting = false;
    }
    static uint32_t pathnum[MAX];
    stack<uint32_t> topo;
    to_visit.push(root); visited[root] = mtime;
    parent[root] = root; pathnum[root] = A[root];
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        topo.push(u);
        children[u].clear();
        pathnums[pathnum[u]]++;
        for(uint32_t v : graph[u])
        {
            if(not locked[v] and visited[v] != mtime)
            {
                to_visit.push(v); visited[v] = mtime;
                parent[v] = u;
                children[u].push_back(v);
                pathnum[v] = gcd(pathnum[u], A[v]);
            }
        }
    }
    while(not topo.empty())
    {
        uint32_t u = topo.top(); topo.pop();
        subtree[u] = 1;
        for(uint32_t v : children[u])
            subtree[u] += subtree[v];
    }
}

unordered_map<uint32_t, uint64_t> solution;

map<uint32_t, uint64_t>
solve(uint32_t root)
{
    mtime++;
    uint32_t asize = graph[root].size();
    for(uint32_t v : graph[root])
        if(locked[v])
            asize--;
    if(asize == 0)
    {
        //cout << "base: " << root+1 << endl;
        solution[A[root]]++;
        return {{A[root], 1}};
    }
    map<uint32_t, uint64_t> rootpaths;
    root_in_vertex(root, rootpaths);
    uint32_t c = root, last_c = root;
    bool found = false;
    while(not found)
    {
        //cout << "candidate " << c+1 << " " << last_c+1 << endl;
        bool c_ok = (subtree[root] - subtree[c]) <= (subtree[root]+1)/2;
        //cout << " parent subtree " << (subtree[root] - subtree[c]) << endl;
        uint32_t max_v = -1u;
        for(uint32_t v : children[c])
        {
            //cout << " " << v+1 << " subtree " << subtree[v] << endl;
            if(subtree[v] > (subtree[root]+1)/2)
                c_ok = false;
            if(v != last_c and (max_v == -1u or subtree[v] > subtree[max_v]))
                max_v = v;
        }
        if(parent[c] != last_c and (max_v == -1u or subtree[parent[c]] > subtree[max_v]))
            max_v = parent[c];
        last_c = c;
        if(c_ok)
            found = true;
        else
            c = max_v;
    }
    //cout << "centroid for " << root+1 << ": " << c+1 << endl;
    solution[A[c]]++;
    vector<uint32_t> divs;
    for(uint32_t d = 1; d * d <= A[c]; d++)
    {
        if(A[c] % d == 0)
            divs.push_back(d);
    }
    for(uint32_t i = divs.size(); i --> 0; )
    {
        if(divs[i] * divs[i] != A[c])
            divs.push_back(A[c] / divs[i]);
    }
    vector<uint64_t> cpaths(divs.size(), 0);
    locked[c] = true;
    children[c].clear();
    for(uint32_t v : graph[c])
    {
        if(not locked[v])
        {
            //cout << " (" << c+1 << ") -> " << v+1 << endl;
            auto partial = solve(v);
            for(auto p : partial)
            {
                solution[gcd(p.first, A[c])] += p.second;
                for(uint32_t i = 0; i < divs.size(); i++)
                    if(cpaths[i])
                        solution[gcd(p.first, divs[i])] += p.second * cpaths[i];
            }
            for(auto p : partial)
                cpaths[lower_bound(divs.begin(), divs.end(),
                                   gcd(p.first, A[c])) - divs.begin()]
                    += p.second;
        }
    }
    return rootpaths;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    bool all_same = true;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(i and A[i-1] != A[i])
            all_same = false;
    }
    if(all_same)
    {
        cout << A[0] << " " << uint64_t(n) * uint64_t(n+1) / 2LLU;
        return 0;
    }
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    solution.reserve(n * 50);
    solve(0);
    vector<pair<uint32_t, uint64_t>> result;
    for(auto p : solution)
        result.push_back(p);
    sort(result.begin(), result.end());
    for(auto p : result)
        cout << p.first << " " << p.second << "\n";
}
