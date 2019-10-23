#include <bits/stdc++.h>

using namespace std;

struct vertex;
using vertex_ref = reference_wrapper<vertex>;

struct vertex
{
    static vertex dummy;

    size_t i = SIZE_MAX;
    vector<vertex_ref> conn;

    size_t preorder = 0, postorder = 0, low = SIZE_MAX;
    bool vis = false;
    vertex_ref parent = dummy;

    size_t subtree_size;
    uint64_t result = 0;
};
vertex vertex::dummy;

bool operator== (const vertex& a, const vertex& b) { return a.i == b.i; }
bool operator!= (const vertex& a, const vertex& b) { return a.i != b.i; }
ostream& operator<< (ostream& out, const vertex& v)
{
    return out << "V(" << v.i << ")";
}

vertex& V(size_t i)
{
    static vector<vertex> vertices;
    while(vertices.size() <= i)
        vertices.emplace_back(), vertices.back().i = vertices.size() - 1;
    return vertices[i];
}

struct dfs_tree
{
    size_t n, root_i;
    size_t the_clock = 0;

    dfs_tree(size_t _n, size_t _root = 1) : n(_n), root_i(_root)
    {
        dfs(V(root_i));
    }

    void dfs(vertex& v)
    {
        v.vis = true;
        v.low = v.preorder = ++the_clock;

        v.subtree_size = 1;
        v.result = 2 * (n - 1);
        size_t sep = 0;
        for(vertex& u : v.conn)
        {
            if(u == v.parent)
                continue;
            else if(u.vis)
                v.low = min(v.low, u.preorder);
            else
            {
                u.parent = v;
                dfs(u);
                v.low = min(v.low, u.low);
                if(u.low >= v.preorder)
                {
                    sep += u.subtree_size;
                    auto w = u.subtree_size * uint64_t(n - u.subtree_size - 1);
                    v.result += w;
                }
                v.subtree_size += u.subtree_size;
            }
        }
        v.result += sep * uint64_t(n - sep - 1);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    V(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        V(u).conn.push_back(V(v));
        V(v).conn.push_back(V(u));
    }

    dfs_tree T(n);

    for(size_t i = 1; i <= n; i++)
        cout << V(i).result << '\n';
}
