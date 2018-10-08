#include <bits/stdc++.h>
#include <ext/functional>

using namespace std;
using __gnu_cxx::identity_element;

template<typename T, typename ChildrenOp,
         typename MT, typename MutateOp, typename MergeOp>
struct segment_tree_i
{
    ChildrenOp F;
    MutateOp M;
    MergeOp S;
    size_t w;
    vector<T> values;
    vector<MT> mutate;
    segment_tree_i(size_t n, ChildrenOp f = {}, MutateOp m = {}, MergeOp s = {})
    {
        F = move(f); M = move(m); S = move(s);
        w = 1 << (31 - __builtin_clz(2*n-1));
        values.resize(2*w, identity_element(F));
        mutate.resize(2*w, identity_element(M));
    }
    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        M(i, nodeL, nodeR, values, mutate);
    }
    T get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or nodeL > getR)
            return identity_element(F);
        else if(getL <= nodeL and nodeR <= getR)
            return values[i];
        else
        {
            return F(get(2*i, nodeL, (nodeL+nodeR)/2, getL, getR),
                     get(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR));
        }
    }
    T get(size_t getL, size_t getR) { return get(1, 0, w-1, getL, getR); }
    void mut(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, MT value)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or nodeL > getR)
            {}
        else if(getL <= nodeL and nodeR <= getR)
        {
            mutate[i] = S(mutate[i], value);
            pull(i, nodeL, nodeR);
        }
        else
        {
            mut(2*i, nodeL, (nodeL+nodeR)/2, getL, getR, value);
            mut(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR, value);
            values[i] = F(values[2*i], values[2*i+1]);
        }
    }
    void mut(size_t getL, size_t getR, MT value) { return mut(1, 0, w-1, getL, getR, value); }
};

struct apply_add
{
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<int32_t>& values, vector<int32_t>& mutate)
    {
        values[i] += (nodeR - nodeL + 1) * mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        mutate[i] = 0;
    }
};
inline int32_t identity_element(apply_add o) { (void)o; return 0; }

typedef segment_tree_i<
    int32_t, plus<int32_t>,
    int32_t, apply_add, plus<int32_t>
> polis_segment_tree;

void dfs_order(uint32_t u, vector<vector<uint32_t>>& graph,
               vector<uint32_t>& preorder, vector<uint32_t>& postorder,
               vector<uint32_t>& depth, uint32_t& currtime, uint32_t b = -1u)
{
    preorder[u] = currtime++;
    for(uint32_t v : graph[u]) if(v != b)
    {
        depth[v] = depth[u] + 1;
        dfs_order(v, graph, preorder, postorder, depth, currtime, u);
    }
    postorder[u] = currtime;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<vector<uint32_t>> graph(n);
    vector<uint32_t> preorder(n), postorder(n), depth(n);
    uint32_t currtime = 0;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs_order(0, graph, preorder, postorder, depth, currtime);
    polis_segment_tree tree(n);
    uint32_t q;
    cin >> q; q += n - 1;
    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == 'W')
        {
            uint32_t u;
            cin >> u; u--;
            cout << depth[u] - tree.get(preorder[u], preorder[u]) << "\n";
        }
        else if(c == 'A')
        {
            uint32_t u, v;
            cin >> u >> v; u--; v--;
            if(preorder[v] < preorder[u]) swap(u, v);
            tree.mut(preorder[v], postorder[v]-1, 1);
        }
    }
}
