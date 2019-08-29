#include <bits/stdc++.h>

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

#define for_each_child(__name) for(auto __name : graph[u]) if(__name != parent[u])

using namespace std;

vector<bool> color;
vector<vector<size_t>> graph;
vector<size_t> parent;
vector<size_t> topo;

vector<int64_t> sub_dist_sum1, dist_sum1;
vector<int> sub_count1;
vector<int64_t> sub_dist_sum, dist_sum;
vector<int> sub_count;

void recompute_sub_dist_sum()
{
    for(auto u : topo)
    {
        sub_count[u] = 1;
        sub_dist_sum[u] = 0;
        for_each_child(v)
        {
            sub_count[u] += sub_count[v];
            sub_dist_sum[u] += sub_dist_sum[v] + sub_count[v];
        }
    }
}

void recompute_sub_dist_sum1()
{
    for(auto u : topo)
    {
        sub_count1[u] = color[u];
        sub_dist_sum1[u] = 0;
        for_each_child(v)
        {
            sub_count1[u] += sub_count1[v];
            sub_dist_sum1[u] += sub_dist_sum1[v] + sub_count1[v];
        }
    }
}

void dfs_dist_sum(size_t u)
{
    dist_sum[u] = sub_dist_sum[u];
    for_each_child(v)
    {
        auto x = sub_dist_sum[u], y = sub_dist_sum[v];
        auto e = sub_count[u], f = sub_count[v];

        sub_dist_sum[u] -= sub_dist_sum[v] + sub_count[v];
        sub_count[u] -= sub_count[v];
        sub_dist_sum[v] += sub_dist_sum[u] + sub_count[u];
        sub_count[v] += sub_count[u];

        dfs_dist_sum(v);

        sub_dist_sum[u] = x;
        sub_dist_sum[v] = y;
        sub_count[u] = e;
        sub_count[v] = f;
    }
}

void dfs_dist_sum1(size_t u)
{
    dist_sum1[u] = sub_dist_sum1[u];
    for_each_child(v)
    {
        auto x = sub_dist_sum1[u], y = sub_dist_sum1[v];
        auto e = sub_count1[u], f = sub_count1[v];

        sub_dist_sum1[u] -= sub_dist_sum1[v] + sub_count1[v];
        sub_count1[u] -= sub_count1[v];
        sub_dist_sum1[v] += sub_dist_sum1[u] + sub_count1[u];
        sub_count1[v] += sub_count1[u];

        dfs_dist_sum1(v);

        sub_dist_sum1[u] = x;
        sub_dist_sum1[v] = y;
        sub_count1[u] = e;
        sub_count1[v] = f;
    }
}

template<typename T, typename BinaryOperation>
struct sparse_table
{
    struct _identity { T operator() (const T& x) const { return x; } };
    BinaryOperation F;
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator, typename TransformOperation = _identity>
    sparse_table(Iterator first, Iterator last, BinaryOperation f = {},
                 TransformOperation t = {}) : F(f)
    {
        n = distance(first, last);
        A.emplace_back(distance(first, last));
        for(size_t i = 0; first != last; first++, i++)
            A[0][i] = t(*first);
        for(size_t i = 1; (1u << i) <= n; i++)
        {
            A.emplace_back(n - (1u << i) + 1);
            for(size_t j = 0; j + (1 << i) <= n; j++)
                A[i][j] = F(A[i-1][j], A[i-1][j + (1u << (i-1))]);
        }
    }
    T operator() (size_t a, size_t b)
    {
        size_t p = __lg(b - a);
        return F(A[p][a], A[p][b - (1 << p)]);
    }
};
struct min_i32 { int operator() (int a, int b) { return min(a, b); } };
using min_table = sparse_table<int, min_i32>;



int main()
{
    size_t n, q;
    ucin >> n >> q;

    // global vector<bool> color;
    color.resize(n+1);
    for(size_t i = 1; i <= n; i++)
    {
        char c;
        ucin >> c;
        color[i] = (c == '1');
    }

    // global vector<vector<size_t>> graph;
    graph.resize(n + 1);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t a, b;
        ucin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> depth(n + 1);
    vector<size_t> vtime(n + 1), of_vtime(3*n + 1);
    vector<int> ett;
    ett.reserve(2*n - 1);
    // global vector<size_t> parent;
    parent.resize(n + 1);
    // global vector<size_t> topo;
    topo.reserve(n);

    size_t dfs_root_time = 0;
    function<void(size_t)> dfs_root = [&](size_t u) {
        vtime[u] = dfs_root_time++;
        of_vtime[vtime[u]] = u;
        ett.push_back(vtime[u]);
        for_each_child(v)
        {
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs_root(v);
            ett.push_back(vtime[u]);
            dfs_root_time++;
        }
        topo.push_back(u);
    };

    dfs_root(1);
    min_table min_vtime(ett.begin(), ett.end());

    sub_dist_sum.resize(n + 1);
    dist_sum.resize(n + 1);
    sub_count.resize(n + 1);
    sub_dist_sum1.resize(n + 1);
    dist_sum1.resize(n + 1);
    sub_count1.resize(n + 1);


    vector<bool> last_color = color;
    recompute_sub_dist_sum();
    recompute_sub_dist_sum1();
    dfs_dist_sum(1);
    dfs_dist_sum1(1);

    const size_t k = 1.37 * floor(sqrt(n));

    vector<size_t> backlog;
    backlog.reserve(k + 3);

    static bool considered[1 << 18];

    vector<tuple<size_t, size_t, bool, size_t>> queries;

    for(size_t t = 1; t <= q; t++)
    {
        size_t type, u;
        ucin >> type >> u;
        if(type == 1)
        {
            backlog.emplace_back(u);
            color[u] = not color[u];
        }
        else if(type == 2)
        {
            int64_t result = dist_sum1[u];
            if(color[u] == 0)
                result = dist_sum[u] - result;
            for(size_t i = backlog.size(); i --> 0; )
            {
                auto v = backlog[i];
                if(considered[v])
                    continue;
                size_t l = vtime[u], r = vtime[v];
                if(l > r) swap(l, r);
                size_t a = of_vtime[min_vtime(l, r+1)];
                int d = depth[u] + depth[v] - 2*depth[a];
                if(color[v] != last_color[v])
                {
                    if(color[v] != color[u])
                        result -= d;
                    else
                        result += d;
                }
                considered[v] = true;
            }
            for(auto v : backlog)
                considered[v] = false;
            ucout << result << '\n';
        }
        if(backlog.size() > k)
        {
            recompute_sub_dist_sum1();
            dfs_dist_sum1(1);
            backlog.clear();
            last_color = color;
        }
    }
}
