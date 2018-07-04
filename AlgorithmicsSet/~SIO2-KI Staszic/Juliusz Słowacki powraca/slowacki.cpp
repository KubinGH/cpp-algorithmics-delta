#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5+16, TSIZE = 1 << 20, MAX_LOG = 17;

uint32_t log2(uint32_t x) { return 31 - __builtin_clz(x); }
template<typename T, size_t N, T(*F)(T, T), T NONE,
        void(*P)(size_t, size_t, size_t, array<T, N>&, array<T, N>&), T SET_NONE,
        T(*S)(T, T) = F>
struct segment_tree_i
{
    array<T, N> values, to_set;
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree_i()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
        fill(to_set.begin(), to_set.end(), SET_NONE);
    }
    void pull(size_t i, size_t tbegin, size_t tend)
    {
        if(to_set[i] != SET_NONE)
        {
            P(i, tbegin, tend, values, to_set);
            to_set[i] = SET_NONE;
        }
    }
    void set(size_t i, size_t tbegin, size_t tend,
                       size_t sbegin, size_t send, T value)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set[i] = S(to_set[i], value);
            pull(i, tbegin, tend);
        }
        else
        {
            set(left(i),  tbegin, (tbegin+tend)/2, sbegin, send, value);
            set(right(i), (tbegin+tend)/2+1, tend, sbegin, send, value);
            values[i] = F(values[left(i)], values[right(i)]);
        }
    }
    void set(size_t sbegin, size_t send, T value)
        { return set(0, 0, N/2 - 1, sbegin, send, value); }
    T get(size_t i, size_t tbegin, size_t tend,
                    size_t sbegin, size_t send)
    {
        pull(i, tbegin, tend);
        if(tend < sbegin or send < tbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return values[i];
        else
            return F(get(left(i),  tbegin, (tbegin+tend)/2, sbegin, send),
                     get(right(i), (tbegin+tend)/2+1, tend, sbegin, send));
    }
    T get(size_t sbegin, size_t send)
        { return get(0, 0, N/2 - 1, sbegin, send); }
    T get(size_t i)
        { return get(i, i); }
};
int32_t add_i32(int32_t a, int32_t b) { return a + b; }
void pull_add(size_t i, size_t tbegin, size_t tend,
              array<int32_t, TSIZE>& values,
              array<int32_t, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        to_set[2*i+1] += to_set[i];
        to_set[2*i+2] += to_set[i];
    }
    values[i] += (tend - tbegin + 1) * to_set[i];
}

segment_tree_i<
    int32_t, TSIZE, add_i32, 0,
    pull_add, 0
> dist_tree;
unordered_map<int32_t, uint32_t> vertex_dict; uint32_t cv = 0;
unordered_map<uint32_t, int32_t> dist[MAX];
uint32_t preorder[MAX], postorder[MAX], order_c = 0;
uint32_t jump[MAX][MAX_LOG], depth[MAX];
vector<pair<uint32_t, int32_t>> graph[MAX];
bitset<MAX> visited;

uint32_t lca(uint32_t u, uint32_t v)
{
    if(u == v)
        return u;
    if(depth[u] < depth[v])
        swap(u, v);
    for(uint32_t p = MAX_LOG; p --> 0;)
    {
        if(depth[u] >= (1u << p) and depth[u] - (1u << p) >= depth[v])
            u = jump[u][p];
    }
    if(u == v)
        return u;
    for(uint32_t p = MAX_LOG; p --> 0;)
    {
        if(depth[u] >= (1u << p) and jump[u][p] != jump[v][p])
            u = jump[u][p], v = jump[v][p];
    }
    return jump[u][0];
}

void dfs_initialization(uint32_t u)
{
    preorder[u] = order_c++;
    for(auto e : graph[u])
    {
        uint32_t v = e.first;
        if(not visited[v])
        {
            depth[v] = depth[u] + 1;
            visited[v] = true;
            jump[v][0] = u;
            for(uint32_t p = 1; p < MAX_LOG; p++)
            {
                uint32_t x = jump[v][p-1];
                if(jump[x][p-1] == -1u)
                    break;
                jump[v][p] = jump[x][p-1];
            }
            dfs_initialization(v);
        }
    }
    postorder[u] = order_c;
}

void dfs_tree_initialization(uint32_t u)
{
    for(auto e : graph[u])
    {
        uint32_t v; int32_t w; tie(v, w) = e;
        if(not visited[v])
        {
            visited[v] = true;
            dist_tree.set(preorder[v], postorder[v]-1, w);
            dfs_tree_initialization(v);
        }
    }
}

void init(vector<tuple<int32_t, int32_t, int32_t>> edges)
{
    for(uint32_t i = 0; i < MAX; i++)
        for(uint32_t j = 0; j < MAX_LOG; j++)
            jump[i][j] = -1u;
    for(auto e : edges)
    {
        int32_t a, b, w;
        tie(a, b, w) = e;
        if(vertex_dict.find(a) == vertex_dict.end())
            vertex_dict[a] = cv++;
        if(vertex_dict.find(b) == vertex_dict.end())
            vertex_dict[b] = cv++;
        uint32_t u = vertex_dict[a], v = vertex_dict[b];
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
        dist[u][v] = w;
        dist[v][u] = w;
    }
    visited[0] = true;
    dfs_initialization(0);
    visited.reset(); visited[0] = true;
    dfs_tree_initialization(0);
}

int32_t distance(int32_t a, int32_t b)
{
    uint32_t u = vertex_dict[a], v = vertex_dict[b];
    return dist_tree.get(preorder[u]) +
           dist_tree.get(preorder[v]) -
           2*dist_tree.get(preorder[lca(u, v)]);
}

void change(int32_t a, int32_t b, int32_t w)
{
    uint32_t u = vertex_dict[a], v = vertex_dict[b];
    if(depth[u] > depth[v])
        swap(u, v);
    dist_tree.set(preorder[v], postorder[v]-1, w - dist[u][v]);
    dist[u][v] = w;
    dist[v][u] = w;
}
