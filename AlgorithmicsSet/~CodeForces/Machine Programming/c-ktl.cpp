#include <ktl/graph/min_cost_flow.cpp>
#include <iostream>
#include <map>

using namespace std;


struct segment { int a, b, c; size_t i; };

int main()
{
    size_t n; int k;
    cin >> n >> k;

    map<int, int> remap;
    vector<segment> A(n);
    for(size_t i = 0; i < n; i++)
    {
        auto& [a, b, c, j] = A[i];
        cin >> a >> b >> c, b += a-1;
        remap[a]; remap[b];
        j = i;
    }

    int m = 0;
    for(auto& [_, v] : remap)
        v = m++;

    for(size_t u = 0; u < n; u++)
    {
        auto& [a, b, _, __] = A[u];
        a = remap[a]; b = remap[b];
    }

    sort(A.begin(), A.end(), [](const segment& lhs, const segment& rhs) {
        return tie(lhs.a, lhs.b) < tie(rhs.a, rhs.b);
    });

    map<int, size_t> begins;
    for(size_t u = n; u --> 0; )
        begins[A[u].a] = u;

    vector<size_t> at;
    min_cost_flow_network<int, int> G(n+2, n, n+1);
    for(size_t u = 0; u < n; u++)
    {
        if(auto it = begins.upper_bound(A[u].b); it != begins.end())
        {
            auto v = it->second;
            G.add_edge(u, v, 1, -A[u].c);
            at.push_back(G.graph[u].size() - 1);
        }
        else
        {
            G.add_edge(u, n+1, 1, -A[u].c);
            at.push_back(G.graph[u].size() - 1);
        }
        if(u+1 < n)
            G.add_edge(u, u+1, k);
    }
    G.add_edge(n, 0, k);
    G.add_edge(n-1, n+1, k);

    G.min_cost_max_flow(k);
    vector<bool> result(n);
    for(size_t u = 0; u < n; u++)
    {
        int f = 0;
        if(at[u] != SIZE_MAX)
            f = G.flow_at(G.graph[u][at[u]]);
        result[A[u].i] = f;
    }

    for(auto b : result)
        cout << b << ' ';
    cout << endl;
}
