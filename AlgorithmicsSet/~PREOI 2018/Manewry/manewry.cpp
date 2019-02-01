#include <bits/stdc++.h>

using namespace std;

typedef tuple<uint32_t, uint32_t, bool, bool, char> dt;

const size_t MAX = 1000;

int main()
{
    uint32_t n, m;
    static array<vector<pair<uint32_t, char> >, MAX> graph;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b; char c;
        cin >> a >> b >> c; a--; b--;
        graph[a].emplace_back(b, c);
    }
    queue<dt> Q;
    unordered_map<dt, dt> prev;
    const dt start(0, 0, 0, 0, 0)
    for(dt p : graph[0])
        Q.emplace_back(p.first, 0, 1, 0, p.second), prev[Q.front()] = start;
    while(not Q.empty())
    {
        dt c = Q.front(); Q.pop();
    }


}
