#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9 + 7;

vector<size_t> A;
vector<vector<size_t>> graph;

void build(size_t u, size_t i, size_t& curr)
{
    for(size_t c = 0; c < A[i]; c++)
    {
        auto v = curr++;
        graph[u].push_back(v);
        graph[v].push_back(u);
        build(v, i + 1, curr);
    }
}

size_t go(size_t u, size_t k)
{
    if(not k)
        return u;
    for(auto v : graph[u])
        if(u < v)
            return go(v, k - 1);
    __builtin_unreachable();
}

void dists(size_t u, size_t d, vector<uint>& out, size_t lock = SIZE_MAX)
{
    out[u] = d;
    for(auto v : graph[u])
        if(v != lock)
            dists(v, d + 1, out, u);
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    size_t m = 1, y = 1;
    A.resize(n);
    for(size_t i = 0; i < n - 1; i++)
        cin >> A[i], m += (y *= A[i]);

    graph.resize(m);
    size_t curr = 1;
    build(0, 0, curr);

    while(q --> 0)
    {
        size_t a, b, c;
        cin >> a >> b >> c; a--; b--; c--;

        auto cv = go(0, c);
        auto av = a > c ? go(graph[cv][(cv!=0)], a - c - 1) : cv;
        auto bv = b > c ? go(graph[cv][(cv!=0) + (av!=cv)], b - c - 1) : cv;

        vector<uint> X(m, UINT_MAX), Y(m, UINT_MAX);
        dists(av, 0, X); dists(bv, 0, Y);
        vector<uint> Z(m);
        for(size_t i = 0; i < m; i++)
            Z[i] = (X[i] + Y[i]) % mod;
        sort(Z.rbegin(), Z.rend());

        uint result = 0;
        for(size_t i = 0; i < m; i += 2)
            result = (result + Z[i]) % mod;
        result = (result + mod) % mod;
        uint sumb = 0;
        for(size_t i = 0; i < m; i++)
            sumb = (sumb + Y[i]) % mod;
        result = (mod + result - (int)sumb) % mod;

        cout << result << '\n';
    }
}
