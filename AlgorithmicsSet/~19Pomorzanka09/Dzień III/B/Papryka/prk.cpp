#include <bits/stdc++.h>

using namespace std;

int64_t k;
vector<int64_t> A;
vector<vector<size_t>> graph;

pair<int64_t, size_t> solve(size_t u, size_t lock = SIZE_MAX)
{
    size_t result = 0;
    vector<int64_t> cont;
    for(auto v : graph[u]) if(v != lock)
    {
        auto below = solve(v, u);
        cont.push_back(below.first);
        result += below.second;
    }
    sort(cont.begin(), cont.end());
    int64_t the_cont = A[u];
    for(auto c : cont)
    {
        if(the_cont + c <= k)
            the_cont += c;
        else
            result++;
    }

    return {the_cont, result};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n >> k;

    A.resize(n); graph.resize(n);

    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << solve(0).second;
}
