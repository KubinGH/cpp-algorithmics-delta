#include <vector>
#include <array>

#include "lib.h"

using namespace std;

const size_t MAX_N = 2e5, MAX_Q = 3e5, MAX_ID = 1e6+0xD, LIM = 512;

struct edge { size_t v, id; };

struct i_like_trains
{
    size_t n;

    vector<vector<edge>> graph;

    array<bool, MAX_ID> reported;
    array<int, MAX_ID> to_pay;

    i_like_trains() {}
    i_like_trains(size_t _n) : n(_n), graph(n)
    {
        reported.fill(false);
        to_pay.fill(0);
    }

    void add_edge(size_t id, size_t u, size_t v, int w)
    {
        graph[u].push_back({v, id});
        graph[v].push_back({u, id});
        to_pay[id] = w;
    }

    void aura(size_t u, int k)
    {
        for(size_t i = 0; i < graph[u].size(); i++)
        {
            auto& e = graph[u][i];
            auto& t = to_pay[e.id];
            if(t <= 0)
                continue;
            t -= k;
            if(t <= 0)
                done(e.id);
        }
    }

    void done(size_t id)
    {
        if(reported[id])
            return;
        reported[id] = true;
        sfinansowano(id);
    }
} ton;

void inicjuj(int n)
{
    ton = i_like_trains(n);
}
void nowyProjekt(int id, int m1, int m2, int k)
{
    ton.add_edge(id, m1 - 1, m2 - 1, k);
}
void dofinansowanie(int m, int k)
{
    ton.aura(m - 1, k);
}
