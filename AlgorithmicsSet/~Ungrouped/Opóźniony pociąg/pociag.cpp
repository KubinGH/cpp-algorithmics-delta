#include <bits/stdc++.h>
#define MAX 1000000
#define MAX_UINT64 numeric_limits<uint64_t>::max()

using namespace std;

struct graph_edge_t
{
    uint32_t target, cost;
    graph_edge_t(uint32_t a_target, uint32_t a_cost)
    {
        target = a_target; cost = a_cost;
    }
    bool operator==(graph_edge_t other) const
    {
        return target == other.target and cost == other.cost;
    }
};

struct graph_edge_hash
{
    int64_t operator() (graph_edge_t& obj) const noexcept
    {
        return int64_t(obj.cost) << 32 | obj.target;
    }
};

typedef unordered_set<graph_edge_t, graph_edge_hash> edges_t;
typedef unordered_map<uint32_t, edges_t> graph_t;
typedef pair<uint32_t, edges_t> graph_pair_t;
typedef pair<uint64_t, uint32_t> queue_item_t;

int main()
{
    uint32_t stations, tunnels;
    cin >> stations >> tunnels;
    uint32_t initial = 0, goal = stations - 1;
    graph_t graph;
    for(uint32_t i = 0; i < tunnels; i++)
    {
        uint32_t a, b, c;
        cin >> a >> b >> c; a--; b--;
        graph[a].insert(graph_edge_t(b, c));
        graph[b].insert(graph_edge_t(a, c));
    }
    // create same sibling graph
    for(uint32_t i = 0; i < stations; i++)
    {
        if(i != goal) for(graph_edge_t edge : graph[i])
        {
            graph[i + MAX].insert(graph_edge_t(edge.target != goal ? edge.target + MAX : edge.target, edge.cost));
        }
    }
    for(uint32_t i = 0; i < stations; i++)
    {
        for(graph_edge_t edge : graph[i])
        {
            if(edge.target < MAX)
                graph[i].insert(graph_edge_t(edge.target != goal ? edge.target + MAX : edge.target, 1));
        }
    }
    for(graph_pair_t cpair : graph)
    {
        for(graph_edge_t edge : cpair.second)
        {
            printf("%u -> %u @ %u\n", cpair.first, edge.target, edge.cost);
        }
    }
    static bool visited[2 * MAX];
    fill(visited, visited + 2*MAX, false);
    visited[initial] = true;
    unordered_map<uint32_t, uint64_t> distance; // from initial
    for(uint32_t i = 0; i < stations; i++)
    {
        if(i != initial)
            distance[i] = distance[i+MAX] = MAX_UINT64;
    }
    priority_queue<queue_item_t, vector<queue_item_t>, greater<queue_item_t> > to_visit;
    to_visit.push(make_pair(0, initial));
    while(not to_visit.empty())
    {
        queue_item_t cpair = to_visit.top(); to_visit.pop();
        uint64_t cdist = cpair.first;
        uint32_t current = cpair.second;
        for(graph_edge_t edge : graph[current])
        {
            if(visited[edge.target]) continue;
            uint64_t alt = cdist + edge.cost;
            if(alt < distance[edge.target])
            {
                distance[edge.target] = alt;
            }
            to_visit.push(make_pair(distance[edge.target], edge.target));
            visited[edge.target] = true;
        }
    }
    if(distance[goal] != MAX_UINT64)
    {
        cout << "WINCYJ ZADAN!" << endl;
        cout << distance[goal];
    }
    else
    {
        cout << "OTOZ NIE" << endl;
    }
}
