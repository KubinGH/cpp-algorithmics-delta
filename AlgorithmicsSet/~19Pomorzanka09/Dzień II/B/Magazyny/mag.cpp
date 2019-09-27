#include <bits/stdc++.h>

using namespace std;

const uint NAX = 1 << 19;

int64_t result = 0, target;
static int A[NAX];
static uint* graph[NAX];
static uint degree[NAX];
static bool vis[NAX];
int64_t _here_;

void dfs(uint u)
{
    vis[u] = true;
    _here_ += A[u] - target;
    for(; degree[u] --> 0; ) if(not vis[graph[u][degree[u]]])
    {
        auto before = _here_;
        dfs(graph[u][degree[u]]);
        if(_here_ > before)
            result += _here_ - before;
        else
            result += before - _here_;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint n;
    cin >> n;

    for(uint i = 0; i < n; i++)
        cin >> A[i];

    target = accumulate(A, A + n, 0ll) / n;

    vector<pair<uint, uint>> edges; edges.reserve(n - 1);
    for(uint i = 0; i < n - 1; i++)
    {
        uint u, v;
        cin >> u >> v; u--; v--;
        edges.emplace_back(u, v);
        degree[u]++; degree[v]++;
    }

    for(uint u = 0; u < n; u++)
        graph[u] = new uint[degree[u]];

    vector<uint> I(n);
    for(auto e : edges)
    {
        uint u = e.first, v = e.second;
        graph[u][I[u]++] = v;
        graph[v][I[v]++] = u;
    }

    edges.clear();
    edges.shrink_to_fit();

    srand(1337);
    uint root = rand() % n;

    dfs(root);

    cout << result;

    for(uint u = 0; u < n; u++)
        delete[] graph[u];

}
