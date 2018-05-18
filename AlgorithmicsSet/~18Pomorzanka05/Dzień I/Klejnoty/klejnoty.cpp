#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4;

template<typename T>
T log2floor(T n)
{
    return numeric_limits<T>::digits - __builtin_clz(n);
}

template<typename T, T(*F)(T, T), T NONE>
struct interval_operator
{
    size_t n, t;
    vector<vector<T>> A;
    interval_operator() {}
    template<typename Iterator>
    interval_operator(Iterator tbegin, Iterator tend)
    {
        size_t i = 0;
        A.emplace_back(); A[0].reserve(distance(tbegin, tend));
        for(auto it = tbegin; it != tend; it++, i++)
            A[0].push_back(*it);
        n = i;
        t = log2floor(n);
        for(size_t i = 1; i < t and (1u << i) <= n + 1; i++)
        {
            A.emplace_back();
            A[i].reserve(n + 1 - (1 << i));
            for(size_t j = 0; j < n + 1 - (1 << i); j++)
            {
                A[i].push_back(F(A[i-1][j], A[i-1][j + (1u << (i-1))]));
            }
        }
    }
    T operator() (size_t a, size_t b)
    {
        if(b >= n)
            b = n - 1;
        if(a > b or a >= n)
            return NONE;
        uint32_t p = log2floor(b - a + 1) - 1;
        return F(A[p][a], A[p][b + 1 - (1 << p)]);
    }
};
uint32_t min_u32(uint32_t a, uint32_t b)
{
    return a < b ? a : b;
}
typedef interval_operator<uint32_t, min_u32, 1u<<25> interval_min;

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
    static interval_min T[MAX];
    for(uint32_t u : topo)
    {
        R[u].reserve(n);
        for(uint32_t p = 0; p < n; p++)
        {
            R[u].push_back(p);
            for(uint32_t v : children[u])
            {
                if(p == 0)
                    R[u][p] += T[v](1, n-1);
                else if(p == n - 1)
                    R[u][p] += T[v](0, n-2);
                else
                    R[u][p] += min(T[v](0, p-1), T[v](p+1, n-1));
            }
        }
        T[u] = interval_min(R[u].begin(), R[u].end());
    }
    uint32_t r = -1u;
    for(uint32_t p = 0; p < n; p++)
        r = min(r, R[topo.back()][p]);
    cout << r + n;
}
