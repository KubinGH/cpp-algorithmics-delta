#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <map>

#include "lib.h"

using namespace std;

const size_t MAX_N = 2e5, MAX_Q = 3e5, MAX_ID = 1e6;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

struct plus_min_heap
{
    min_priority_queue<pair<int64_t, size_t>> Q;
    int64_t offset;

    void plus(int64_t x)                { offset += x; }
    void push(int64_t x, size_t i)      { Q.emplace(x - offset, i); }
    pair<int64_t, size_t> min() const   { return {Q.top().first + offset, Q.top().second}; }
    void pop_min()                      { Q.pop(); }
    bool empty() const                  { return Q.empty(); }
    size_t size() const                 { return Q.size(); }
};

struct i_like_trains
{
    size_t n;

    array<plus_min_heap, MAX_N> triggers;
    array<vector<pair<size_t, int64_t>>, MAX_N> cu_aura;
    array<tuple<size_t, size_t, int, size_t>, MAX_ID> conditions;
    array<bool, MAX_ID> reported;
    size_t watch = 0;

    void init(size_t _n)
    {
        n = _n;
        for(size_t i = 0; i < n; i++)
            cu_aura[i].emplace_back(0, 0);
    }

    void set_condition(size_t id, size_t u, size_t v, int w)
    {
        watch++;
        conditions[id] = {u, v, w, watch};
        triggers[u].push((w+1)/2, id);
        triggers[v].push((w+1)/2, id);
    }

    int64_t aura_since(size_t i, size_t l)
    {
        auto it = lower_bound(cu_aura[i].begin(), cu_aura[i].end(), make_pair(l, INT64_MIN));
        return cu_aura[i].back().second - prev(it)->second;
    }

    void aura(size_t a, int k)
    {
        watch++;
        triggers[a].plus(-k);
        cu_aura[a].emplace_back(watch, cu_aura[a].back().second + k);
        while(not triggers[a].empty() and triggers[a].min().first <= 0)
        {
            auto id = triggers[a].min().second;
            auto [u, v, w, t] = conditions[id];
            triggers[a].pop_min();
            auto s = aura_since(u, t) + aura_since(v, t);
            if(s >= w)
                done(id);
            else
                set_condition(id, u, v, w - s);
        }
    }

    void done(size_t id)
    {
        if(reported[id])
            return;
        reported[id] = true;
        sfinansowano(id + 1);
    }
} ton;

void inicjuj(int n)
{
    ton.init(n);
}
void nowyProjekt(int id, int m1, int m2, int k)
{
    ton.set_condition(id - 1, m1 - 1, m2 - 1, k);
}
void dofinansowanie(int m, int k)
{
    ton.aura(m - 1, k);
}
