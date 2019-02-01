#include <bits/stdc++.h>

using namespace std;

struct query { uint32_t t, x, y; };

struct Graph
{
    vector<uint32_t> parent, type;
    vector<vector<uint32_t>> children;
    void clear()
    {
        parent.clear(); children.clear(); type.clear();
    }
    void resize(uint32_t n)
    {
        parent.resize(n); type.resize(n); children.resize(n);
    }
};

struct Decomposition
{
    uint32_t n, p, m;
    Graph base, tree;
    vector<uint32_t> offset, marks, marked, in_mark;
    vector<vector<uint32_t>> counter, vertices;
    Decomposition(uint32_t _n, uint32_t _p, Graph _base)
        : n(_n), p(_p), base(_base), marked(n), in_mark(n) {}
    void rebuild_graph()
    {
        base.clear();
    }
    void dfs_redecomp(uint32_t u, uint32_t i)
    {
        //cout << u << "(" << i << ")" << endl;
        in_mark[u] = i;
        vertices[i].push_back(u);
        counter[in_mark[i]][base.type[i]]++;
        //cout << base.children.size() << endl;
        for(uint32_t v : base.children[u])
        {
            if(marked[v] != -1u)
            {
                tree.parent[marked[v]] = i;
                tree.children[i].push_back(marked[v]);
                dfs_redecomp(v, marked[v]);
            }
            else
                dfs_redecomp(v, i);
        }
    }
    template<typename Iterator>
    void rebuild_decomposition(Iterator first, Iterator last)
    {
        tree.clear(); offset.clear();
        counter.clear(); vertices.clear(); marks.clear();
        fill(marked.begin(), marked.end(), -1u);
        fill(in_mark.begin(), in_mark.end(), -1u);
        #define MARK(u) { if(marked[u] == -1u) marked[u] = marks.size(), marks.push_back(u); }
        MARK(0);
        for(auto it = first; it != last; ++it)
        {
            MARK(it->x);
            if(it->t == 3)
                MARK(it->y);
        }
        #undef MARK
        m = marks.size();
        tree.resize(m); offset.resize(m);
        counter.resize(m, vector<uint32_t>(p)); vertices.resize(m);
        //cout << "dfs" << endl;
        dfs_redecomp(0, marked[0]);
    }
};

struct Environment
{
    uint32_t n, p, split;
    Graph graph;
    Decomposition decomp;
    Environment(uint32_t _n, uint32_t _p)
        : n(_n), p(_p),
          graph({vector<uint32_t>(n), vector<uint32_t>(n),
                 vector<vector<uint32_t>>(n)}),
          decomp(n, p, graph) {}
    void rebuild_graph()
    {
        decomp.rebuild_graph();
        graph = decomp.base;
    }
    template<typename Iterator>
    void rebuild_decomposition(Iterator first, Iterator last)
    {
        decomp.rebuild_decomposition(first, last);
    }

    uint32_t dfs_counter_nonmarked(uint32_t u, uint32_t a, uint32_t offset, bool first = true)
    {
        //cout << "@ " << u << " " << a << endl;
        if(not first and decomp.marked[u] != -1u)
            return 0;
        uint32_t r = 0;
        for(uint32_t v : decomp.tree.children[u])
            r += dfs_counter_nonmarked(v, a, offset, false);
        return r + ((p + decomp.tree.type[u] - offset) == a);
    }
    uint32_t count_type(uint32_t a, uint32_t v)
    {
        uint32_t r = 0;
        for(uint32_t s : decomp.tree.children[decomp.in_mark[v]])
            r += decomp.counter[s][(p + a - decomp.offset[s]) % p];
        return r + dfs_counter_nonmarked(v, a, decomp.offset[decomp.in_mark[v]]);
    }

    void increment_subtree(uint32_t a, uint32_t v)
    {

    }

    void rebind_parent(uint32_t u, uint32_t v)
    {

    }
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, p;
    cin >> n >> p;
    Environment env(n, p);
    for(uint32_t i = 0; i < n; i++)
        cin >> env.graph.type[i];
    for(uint32_t i = 1; i < n; i++)
    {
        cin >> env.graph.parent[i];
        env.graph.children[--env.graph.parent[i]].push_back(i);
    }
    env.decomp.base = env.graph;
    uint32_t q;
    cin >> q;
    env.split = ceil(sqrt(q));
    vector<query> Q(q);
    for(uint32_t i = 0; i < q; i++)
        cin >> Q[i].t >> Q[i].x >> Q[i].y;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        if(qi % env.split == 0)
        {
            if(qi and false)
                env.rebuild_graph();
            //cout << "rebuild " << qi << ".." << min(q, qi+env.split) << endl;
            env.rebuild_decomposition(Q.begin()+qi, Q.begin()+min(q, qi+env.split));
        }
        //cout << "query " << qi << endl;
        if(Q[qi].t == 1)
            cout << env.count_type(Q[qi].x-1, Q[qi].y) << "\n";
        else if(Q[qi].t == 2)
            env.increment_subtree(Q[qi].x-1, Q[qi].y);
        else if(Q[qi].t == 3)
            env.rebind_parent(Q[qi].x-1, Q[qi].y-1);
    }
}
