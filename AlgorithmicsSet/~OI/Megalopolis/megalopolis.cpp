#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 250000, TSIZE = 1 << 19;

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

uint32_t add_u32(uint32_t a, uint32_t b) { return a + b; }
void pull_add(size_t i, size_t tbegin, size_t tend,
              array<uint32_t, TSIZE>& values,
              array<uint32_t, TSIZE>& to_set)
{
    if(tbegin < tend)
    {
        to_set[2*i+1] += to_set[i];
        to_set[2*i+2] += to_set[i];
    }
    values[i] += to_set[i];
}
typedef segment_tree_i<
    uint32_t, TSIZE, add_u32, 0,
    pull_add, 0
> tree_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    static tree_t tree;
    static uint32_t depth[MAX], graphidx[MAX],
                    preorder[MAX], postorder[MAX];
    // NOTE: This is not exactly pre/post order index.
    //       and rather a numbering that satisfies
    //       postorder[u] > preorder[v] for all children v of u
    // It is guaranteed that the subtree of u is contained
    // in the interval [ preorder[u], postorder[u] )
    uint32_t order = 1;
    static bitset<MAX> visited;
    stack<uint32_t> to_visit;
    to_visit.push(0); visited[0] = true;
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top();
        uint32_t& i = graphidx[u];
        for(; i < graph[u].size(); i++)
        {
            uint32_t v = graph[u][i];
            if(not visited[v])
            {
                to_visit.push(v);
                visited[v] = true;
                depth[v] = depth[u] + 1;
                preorder[v] = order++;
                break;
            }
        }
        if(i == graph[u].size())
            postorder[u] = order, to_visit.pop();
    }
    uint32_t m;
    cin >> m;
    for(uint32_t i = 0; i < m + n - 1; i++)
    {
        char c;
        cin >> c;
        if(c == 'A')
        {
            uint32_t u, v;
            cin >> u >> v; u--; v--;
            if(depth[u] > depth[v])
                swap(u, v);
            tree.set(preorder[v], postorder[v]-1, 1);
        }
        else if(c == 'W')
        {
            uint32_t u;
            cin >> u; u--;
            cout << depth[u] - tree.get(preorder[u]) << "\n";
        }
    }
}
