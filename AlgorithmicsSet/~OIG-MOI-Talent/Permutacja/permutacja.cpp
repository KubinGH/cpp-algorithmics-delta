#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18, TSIZE = 1 << 19;

typedef pair<uint32_t, uint32_t> pair_u32;

template<typename T, size_t N, T(*F)(T, T), T(*GET_NONE)()>
struct segment_tree
{
    array<T, N> values;
    static constexpr T NONE = GET_NONE();
    static_assert(__builtin_popcount(N) == 1 and N > 4, "N != 2**k");
    size_t offset() const { return N/2 - 1; }
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
    segment_tree()
    {
        fill(values.begin() + offset(), values.end(), NONE);
        for(size_t i = offset(); i --> 0;)
            values[i] = F(values[left(i)], values[right(i)]);
    }
    void set(size_t i, T value)
    {
        i += offset();
        values[i] = value;
        while(i > 0)
            i = parent(i), values[i] = F(values[left(i)], values[right(i)]);
    }
    T get(size_t sbegin, size_t send)
    {
        //return get(0, 0, N/2 - 1, sbegin, send);
        send++;
        T result = NONE;
        for(sbegin += offset(), send += offset(); sbegin < send;
            sbegin = parent(sbegin), send = parent(send))
        {
            if(sbegin % 2 == 0) result = F(result, values[sbegin++]);
            if(send % 2 == 0)   result = F(result, values[--send]);
        }
        return result;
    }
};
pair_u32 min_2u32(pair_u32 a, pair_u32 b) { return a<b ? a : b; }
constexpr pair_u32 get_none() { return {-1u, -1u}; }
typedef segment_tree<
    pair_u32, TSIZE, min_2u32, get_none
> min_tree;

uint32_t P[MAX];
min_tree tree[3];
map<pair_u32, vector<pair_u32>> G;
map<pair_u32, uint32_t> C;
pair_u32 build_order_graph(uint32_t a, uint32_t b)
{
    if(a == b) return get_none();
    uint32_t i = tree[a%2].get(a, b-2).second,
             j = tree[(a+1)%2].get(i+1, b-1).second;
    pair_u32 result, x, y, z, t = {P[i], P[j]};
    x = build_order_graph(a, i);
    y = build_order_graph(i+1, j);
    z = build_order_graph(j+1, b);
    G[t].push_back(x), C[x]++;
    G[t].push_back(y), C[y]++;
    G[t].push_back(z), C[z]++;
    return t;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> P[i]; P[i]--;
        tree[i%2].set(i, {P[i], i});
        tree[(i+1)%2].set(i, {-1u, i});
        tree[2].set(i, {P[i], i});
    }
    pair_u32 first = build_order_graph(0, n);
    vector<pair_u32> topo;
    priority_queue<pair_u32, vector<pair_u32>, greater<pair_u32>> Q;
    Q.push(first);
    while(not Q.empty())
    {
        pair_u32 u = Q.top(); Q.pop();
        topo.push_back(u);
        for(pair_u32 v : G[u])
            if(--C[v] == 0)
                Q.emplace(v);
    }
    topo.pop_back();
    for(auto x : topo)
        cout << x.first+1 << " " << x.second+1 << " ";
}
