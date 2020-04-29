#pragma GCC optimize("Ofast")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")

#include <iostream>

#include <array>
using std::array;

// -*- ktl/graph/max_flow.cpp -*-

#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>
#include <queue>

using std::min; using std::max; using std::__lg; using std::fill;
using std::vector; using std::queue;
using std::size_t;
using std::numeric_limits;

template<typename flow_t, flow_t ScaleBase = 0>
struct flow_network
{
    constexpr static auto oo = numeric_limits<flow_t>::max() - 0xF;

    struct edge
    {
        size_t s, t;
        flow_t cap; bool rev;
        size_t rev_i;
    };

    size_t n, source, sink;
    array<vector<edge>, 5555> graph;

    array<int, 5555> dist;
    array<size_t, 5555> curr_edge;

    flow_t bound = 1;

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t) {}

    void push(edge& e, flow_t f) { e.cap -= f; graph[e.t][e.rev_i].cap += f; }
    flow_t flow_at(edge& e) { return graph[e.t][e.rev_i].cap; }

    void add_edge(size_t s, size_t t, flow_t cap = +oo)
    {
        graph[s].push_back({s, t, cap, false, graph[t].size()});
        graph[t].push_back({t, s, 0, true, graph[s].size() - 1});
        if(ScaleBase) while(bound < cap) bound *= ScaleBase;
    }

    bool bfs()
    {
        fill(dist.begin(), dist.end(), -1);
        queue<size_t> Q;
        Q.push(source); dist[source] = 0;
        while(not Q.empty() and dist[sink] == -1)
        {
            auto u = Q.front(); Q.pop();
            for(auto& e : graph[u])
                if(e.cap >= bound and dist[e.t] == -1)
                    Q.push(e.t), dist[e.t] = dist[u] + 1;
        }
        if(ScaleBase and dist[sink] == -1 and bound > 1)
        {
            bound /= ScaleBase;
            if(not bound) bound = 1;
            return bfs();
        }
        return dist[sink] != -1;
    }

    flow_t augment_dfs(size_t u, flow_t lim)
    {
        if(u == sink or not lim)
            return lim;
        flow_t delta = 0;
        for(size_t& j = curr_edge[u]; j < graph[u].size(); j++)
        {
            auto& e = graph[u][j]; const auto v = e.t;
            if(e.cap and dist[v] == dist[u] + 1)
            {
                auto x = augment_dfs(v, min(lim - delta, e.cap));
                push(e, x); delta += x;
            }
            if(delta == lim)
                return lim;
        }
        if(not delta)
            dist[u] = -1;
        return delta;
    }

    flow_t max_flow()
    {
        flow_t flow = 0;
        while(bfs())
        {
            fill(curr_edge.begin(), curr_edge.end(), 0);
            flow += augment_dfs(source, +oo);
        }
        return flow;
    }
};

// -$- ktl/graph/max_flow.cpp -$-


// -*- ktl/util/fastio.cpp -*-

#include <cstdint>
#include <cstdio>
#include <type_traits>
#include <iostream>

#ifdef _WIN32
#define getchar_unlocked getchar
#define putchar_unlocked putchar
#define fputs_unlocked fputs
#endif

using std::is_integral; using std::is_unsigned; using std::is_signed;
using std::make_unsigned;
using std::enable_if;

struct unlocked_cin
{
    char _whitespace_skip()
    {
        char lchar;
        while(isspace(lchar = getchar_unlocked())) {}
        return lchar;
    }
    unlocked_cin& operator>> (char& x)
    {
        x = _whitespace_skip();
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        x = 0;
        char lchar = _whitespace_skip();
        do {
            x *= 10, x += lchar - '0';
        } while(isdigit(lchar = getchar_unlocked()));
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cin&>::type
    operator>> (T& x)
    {
        bool s = false;
        x = 0;
        char lchar = _whitespace_skip();
        if(lchar == '-')
            s = true;
        else
            x += lchar - '0';
        while(isdigit(lchar = getchar_unlocked()))
            x *= 10, x += lchar - '0';
        if(s) x = -x;
        return *this;
    }
} ucin;

struct unlocked_cout
{
    unlocked_cout& operator<< (const char* c)
    {
        fputs_unlocked(c, stdout);
        return *this;
    }
    unlocked_cout& operator<< (char x)
    {
        putchar_unlocked(x);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_unsigned<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        static char buffer[64];
        size_t i = 0;
        if(not x)
            buffer[i++] = '0';
        while(x)
            buffer[i++] = (x % 10) + '0', x /= 10;
        for(; i --> 0; )
            putchar_unlocked(buffer[i]);
        return *this;
    }
    template<typename T>
    typename enable_if<is_integral<T>::value && is_signed<T>::value, unlocked_cout&>::type
    operator<< (T x)
    {
        if(x < 0)
            putchar_unlocked('-'), x = -x;
        return *this << static_cast<typename make_unsigned<T>::type>(x);
    }
} ucout;

// -$- ktl/util/fastio.cpp -$-


using namespace std;

int main()
{
    size_t n, m;
    ucin >> n >> m;

    flow_network<uint64_t, 22> G(n, 0, n - 1);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint64_t c;
        ucin >> u >> v >> c; u--; v--;
        G.add_edge(u, v, c);
        G.add_edge(v, u, c);
    }

    ucout << G.max_flow();
}
