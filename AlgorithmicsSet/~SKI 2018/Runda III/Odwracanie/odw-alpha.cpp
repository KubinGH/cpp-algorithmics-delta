#include <bits/stdc++.h>

using namespace std;

const uint32_t GRAND_LIM = 128;

template<typename T>
constexpr inline T lsb(T x) { return x & (-x); }

template<typename T>
struct fenwick_tree
{
    size_t n;
    T* F;
    fenwick_tree(size_t _n) { n = _n+1; F = new T[n+1]; fill(F, F + (n+1), 0); }
    ~fenwick_tree() { delete[] F; }
    T get_prefix(size_t p) const // Sum in [0, p)
        { T r = 0; p++; while(p) r += F[p], p -= lsb(p); return r; }
    void delta(size_t p, T v)
        { p += 2; while(p <= n) F[p] += v, p += lsb(p); }

    T get(size_t a, size_t b) const // Get on interval [a, b]
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const // Get on point [p]
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t root = -1u;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t m;
        cin >> m;
        while(m --> 0)
        {
            int32_t a;
            cin >> a;
            if(a == -1) root = i, graph[i].push_back(-1u);
            else graph[i].push_back(a-1);
        }
    }
    //cerr << "done input" << endl;

    //cerr << "root = " << root+1 << endl;
    // root and find children order
    vector<vector<uint32_t>> children(n);
    vector<uint32_t> parent(n);
    stack<uint32_t> tovis;
    parent[root] = -1u; tovis.push(root);
    while(not tovis.empty())
    {
        uint32_t u = tovis.top(); tovis.pop();
        //cerr << "@ " << u+1 << endl;
        const auto& G = graph[u];
        uint32_t p = find(G.begin(), G.end(), parent[u]) - G.begin();
        if(G.size() > 1) for(uint32_t i = (p+1) % G.size(); i != p; i = (i+1) % G.size())
        {
            //cerr << " -> " << G[i]+1 << endl;
            tovis.push(G[i]);
            parent[G[i]] = u;
            children[u].push_back(G[i]);
        }
    }
    //cerr << "done root" << endl;

    // find preorder, postorder and base door count for each
    vector<uint32_t> edge_idx(n), preorder(n, -1u), postorder(n, -1u);
    tovis.push(root);
    uint32_t currtime = 0;
    while(not tovis.empty())
    {
        uint32_t u = tovis.top();
        if(preorder[u] == -1u) preorder[u] = currtime++;
        if(edge_idx[u] < children[u].size())
        {
            tovis.push(children[u][edge_idx[u]++]);
        }
        if(u == tovis.top())
        {
            postorder[u] = currtime++;
            tovis.pop();
        }
    }
    //for(uint32_t i = 0; i < n; i++)
    //    cerr << i+1 << ": " << preorder[i] << "/" << postorder[i] << endl;
    //cerr << "done ordering" << endl;

    // compute flip costs and find grand vertices
    vector<bool> is_grand(n);
    vector<uint32_t> grand, as_grand(n, -1u);
    vector<vector<uint32_t>> grand_subs;
    vector<vector<int32_t>> flip_cost(n);
    tovis.push(root);
    while(not tovis.empty())
    {
        uint32_t u = tovis.top(); tovis.pop();
        if(children[u].empty()) continue;
        for(uint32_t v : children[u])
            tovis.push(v);
        uint32_t m = children[u].size();
        flip_cost[u].resize(m);
        int32_t o = preorder[u];
        for(uint32_t i = m; i --> 0; )
        {
            uint32_t v = children[u][i];
            flip_cost[u][i] = (o + 1) - preorder[v];
            o += postorder[v] - preorder[v] + 1;
        }
        if(children[u].size() > GRAND_LIM)
        {
            is_grand[u] = true; as_grand[u] = grand.size();
            grand.push_back(u);
            grand_subs.emplace_back(n, -1u);
            stack<pair<uint32_t, uint32_t>> subtovis;
            for(uint32_t i = 0; i < m; i++)
                subtovis.emplace(children[u][i], i);
            while(not subtovis.empty())
            {
                auto p = subtovis.top(); subtovis.pop();
                grand_subs.back()[p.first] = p.second;
                for(uint32_t w : children[p.first])
                    subtovis.emplace(w, p.second);
            }
        }
        //cerr << u << ": ";
        //for(uint32_t i = 0; i < m; i++)
        //    cerr << children[u][i]+1 << " @ " << flip_cost[u][i] << "; ";
        //cerr << endl;
    }
    //cerr << "done flip cost" << endl;

    fenwick_tree<int32_t> cost(postorder[root]+2);
    vector<bool> flipped(n);
    for(uint32_t i = 0; i <= postorder[root]; i++)
        cost.delta(i, 1);
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        char c; uint32_t u;
        cin >> c >> u; u--;
        if(c == 'p')
        {
            int32_t b = cost.get_prefix(preorder[u]+1);
            for(uint32_t i = 0; i < grand.size(); i++)
            {
                uint32_t g = grand[i];
                if(flipped[g] and grand_subs[i][u] != -1u)
                    b += flip_cost[g][grand_subs[i][u]];
            }
            cout << b << "\n";
        }
        else if(c == 'z')
        {
            int32_t s = flipped[u] ? -1 : 1;
            uint32_t m = children[u].size();
            if(not is_grand[u])
            {
                for(uint32_t i = 0; i < m; i++)
                {
                    uint32_t v = children[u][i];
                    cost.delta(preorder[v], s * flip_cost[u][i]);
                    cost.delta(postorder[v]+1, -s * flip_cost[u][i]);
                }
            }
            flipped[u] = not flipped[u];
        }
        //for(uint32_t i = 0; i <= postorder[u]; i++)
        //    cerr << cost.get_prefix(i+1) << " "; cerr << endl;
    }
}
