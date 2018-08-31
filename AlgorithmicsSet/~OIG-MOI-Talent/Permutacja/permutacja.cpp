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

uint32_t P[MAX], T[MAX], C[MAX];
vector<uint32_t> G[MAX];
min_tree tree[2];
pair_u32 build_order_graph(uint32_t a, uint32_t b)
{
    if(a == b) return {MAX-1, MAX-1};
    uint32_t i = tree[a%2].get(a, b-2).second,
             j = tree[(a+1)%2].get(i+1, b-1).second;
    pair_u32 result, x, y, z, t = {P[i], P[j]};
    x = build_order_graph(a, i);
    y = build_order_graph(i+1, j);
    z = build_order_graph(j+1, b);
    G[t.first].push_back(x.first), C[x.first]++;
    G[t.first].push_back(y.first), C[y.first]++;
    G[t.first].push_back(z.first), C[z.first]++;
    T[t.first] = t.second;
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
    }
    uint32_t first = build_order_graph(0, n).first;
    static uint32_t topo[MAX]; uint32_t ti = 0;
    priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t>> Q;
    Q.push(first);
    while(not Q.empty())
    {
        uint32_t u = Q.top(); Q.pop();
        topo[ti++] = u;
        for(uint32_t v : G[u])
            if(--C[v] == 0)
                Q.emplace(v);
    }
    ti--;
    for(uint32_t i = 0; i < ti; i++)
        cout << topo[i]+1 << " " << T[topo[i]]+1 << " ";
}
