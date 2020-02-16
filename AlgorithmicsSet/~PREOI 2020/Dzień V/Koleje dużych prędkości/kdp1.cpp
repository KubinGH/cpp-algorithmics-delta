#include <vector>
#include <array>
#include <queue>
#include <map>
#include <set>

#include "lib.h"

using namespace std;

const size_t MAX_N = 2e5, MAX_Q = 3e5, MAX_ID = 1e6+0xD, LIM = 512;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

struct plus_min_heap
{
    min_priority_queue<pair<int64_t, size_t>> Q;
    int64_t offset;

    void add_to_all(int64_t x)
    {
        offset += x;
    }
    void push(int64_t x, size_t i)
    {
        Q.emplace(x - offset, i);
    }
    pair<int64_t, size_t> min() const
    {
        return {Q.top().first + offset, Q.top().second};
    }
    void pop_min()
    {
        Q.pop();
    }
};
struct cool_heap
{
    map<int64_t, set<size_t>> values;
    map<size_t, int64_t> value_of;
    void push(int64_t x, size_t i)
    {
        values[x].insert(i);
        value_of[i] = x;
    }
    void _move(size_t i, int64_t x, int64_t y)
    {
        values[x].erase(i);
        if(values[x].empty()) values.erase(x);
        values[y].insert(i);
        value_of[i] = y;
    }
    void add_to_index(int64_t x, size_t i)
    {
        _move(i, value_of[i], value_of[i] + x);
    }
    pair<int64_t, size_t> min() const
    {
        return {values.begin()->first, *(values.begin()->second.begin())};
    }
    void pop_min()
    {
        values.begin()->second.erase(values.begin()->second.begin());
        if(values.begin()->second.empty())
            values.erase(values.begin());
    }
};

struct city
{
    
};





struct edge { size_t v, id; };

struct i_like_trains
{
    size_t n;

    vector<vector<edge>> graph;

    array<bool, MAX_ID> reported;

    i_like_trains() {}
    i_like_trains(size_t _n) : n(_n), graph(n)
    {
        reported.fill(false);
    }

    void add_edge(size_t id, size_t u, size_t v, int w)
    {
        (void)id; (void)u; (void)v; (void)w;
    }

    void aura(size_t u, int k)
    {
        (void)u; (void)k;
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
