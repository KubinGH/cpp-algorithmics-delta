#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const uint64_t INF = numeric_limits<uint64_t>::max();

typedef pair<uint64_t, uint64_t> upair;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, m;
    cin >> n >> m;
    static array<vector<upair>, MAX> graph;
    for(uint64_t i = 0; i < m; i++)
    {
        uint64_t a, b, w;
        cin >> a >> b >> w; a--; b--;
        graph[b].emplace_back(a, w);
        graph[a].emplace_back(b, w);

    }
    static array<uint64_t, MAX> distance;
    priority_queue<upair, vector<upair>, greater<upair> > Q;
    distance[0] = 0;
    Q.push(make_pair(0, 0));
    for(uint64_t i = 1; i < n; i++)
    {
        distance[i] = INF;
        Q.push(make_pair(INF, i));
    }
    while(not Q.empty())
    {
        upair current = Q.top(); Q.pop();
        uint64_t d = current.first, c = current.second;
        if(d > distance[c] or d == INF) continue;
        for(upair k : graph[c])
        {
            uint64_t kc = k.first, kd = k.second;
            if(distance[kc] > distance[c] + kd)
            {
                distance[kc] = distance[c] + kd;
                Q.push(make_pair(distance[kc], kc));
            }
        }
    }
    for(uint64_t i = 0; i < n; i++)
    {
        if(distance[i] == INF)
            cout << -1 << '\n';
        else
            cout << distance[i] << '\n';
    }

}
