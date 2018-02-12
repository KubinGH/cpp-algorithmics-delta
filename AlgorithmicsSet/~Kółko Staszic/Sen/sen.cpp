#include <bits/stdc++.h>

using namespace std;

struct edge_t
{
    uint32_t target, weight;
    edge_t(uint32_t t, uint32_t w) { target = t; weight = w; }
    edge_t() {target = weight = 0;};
};

const size_t MAX = 823543;
const uint32_t INF = numeric_limits<uint32_t>::max();

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<vector<edge_t>, MAX> graph;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t a, b, c;
        cin >> a >> b >> c; a--; b--;
        graph[a].emplace_back(b, c);
        graph[b].emplace_back(a, c);
    }
    static array<edge_t, MAX> P;
    static array<bool, MAX> V;
    V[0] = true;
    P[0] = edge_t(0, 0);
    queue<uint32_t> Q; Q.push(0);
    while(not Q.empty())
    {
        uint32_t current = Q.front(); Q.pop();
        for(edge_t next : graph[current])
        {
            if(not V[next.target])
            {
                P[next.target].target = current;
                P[next.target].weight = next.weight;
                Q.push(next.target);
                V[next.target] = true;
            }
        }
    }
    static array<uint32_t, MAX> R;
    R[0] = 0;
    for(uint32_t i = 1; i < n; i++)
        R[i] = INF;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t c;
        cin >> c; c--;
        uint32_t r = 0;
        stack<uint32_t> S;
        while(P[c].target != c)
        {
            r ^= P[c].weight;
            S.push(c);
            if(R[P[c].target] != INF)
            {
                r ^= R[P[c].target];
                break;
            }
            else
                c = P[c].target;
        }
        while(not S.empty())
            R[S.top()] = P[S.top()].weight ^ R[P[S.top()].target], S.pop();
        cout << r << '\n';
    }

}
