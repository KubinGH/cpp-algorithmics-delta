#include <bits/stdc++.h>

using namespace std;

struct segment_bush
{
    struct node
    {
        node *left, *right;
        int32_t value, mutate;
        node() : left(nullptr), right(nullptr), value(0), mutate(0) {}
        void assert_children()
        {
            if(left == nullptr) left = new node();
            if(right == nullptr) right = new node();
        }
    } root;
    int64_t L, R;
    segment_bush(int64_t _L, int64_t _R) : L(_L), R(_R) {}
    void pull(node* n, uint32_t nodeL, uint32_t nodeR)
    {
        if(nodeL < nodeR)
        {
            n->assert_children();
            n->left->mutate += n->mutate;
            n->right->mutate += n->mutate;
        }
        n->value += n->mutate * (nodeR - nodeL + 1);
        n->mutate = 0;
    }
    int32_t get(node* n, uint32_t nodeL, uint32_t nodeR, uint32_t getL, uint32_t getR)
    {
        pull(n, nodeL, nodeR);
        if(getR < nodeL or nodeR < getL)
            return 0;
        else if(getL <= nodeL and nodeR <= getR)
            return n->value;
        else
        {
            return (n->left  ? get(n->left,  nodeL,   (nodeL+nodeR)/2, getL, getR) : 0) +
                   (n->right ? get(n->right, (nodeL+nodeR)/2+1, nodeR, getL, getR) : 0);
        }
    }
    int32_t get(int64_t getL, int64_t getR)
    {
        return get(&root, 0, R-L, max(0ll, getL-L), min(R-L, getR-L));
    }
    void mut(node* n, uint32_t nodeL, uint32_t nodeR, uint32_t getL, uint32_t getR, int32_t value)
    {
        //cout << int(nodeL-((1<<30)+1)) << ".." << int(nodeR-((1<<30)+1)) << endl;
        pull(n, nodeL, nodeR);
        if(getR < nodeL or nodeR < getL)
            {}
        else if(getL <= nodeL and nodeR <= getR)
        {
            n->mutate += value;
            pull(n, nodeL, nodeR);
        }
        else
        {
            if(n->left)
                mut(n->left,  nodeL,   (nodeL+nodeR)/2, getL, getR, value);
            if(n->right)
                mut(n->right, (nodeL+nodeR)/2+1, nodeR, getL, getR, value);
            n->value = (n->left ? n->left->value : 0) + (n->right ? n->right->value : 0);
        }
    }
    void mut(int64_t getL, int64_t getR, int32_t value)
    {
        mut(&root, 0, R-L, max(0ll, getL-L), min(R-L, getR-L), value);
    }
};

struct query_t
{
    uint32_t t, i; int32_t L, R;
};

template<typename T>
T lomul(T x, T m)
{
    T r = x;
    if(x % m)
        r += (m - x%m);
    return r;
}
template<typename T>
T himul(T x, T m)
{
    return x - x%m;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<uint64_t> step(n+1);
    vector<uint32_t> group(n+1, 1);
    step[0] = 1;
    for(uint32_t i = 1; i <= n; i++)
    {
        uint64_t d; cin >> d;
        step[i] = lomul(d, step[i-1]);
        if(step[i] > (1LLU<<32))
            { n = i-1; break; }
        if(step[i] == step[i-1])
        {
            if(group[i-1] == 1)
                group[i] = -1u;
            else
                group[i] = group[i-1] - 1;
            group[i + group[i]]++;
        }
    }
    //for(uint32_t i = 0; i <= n; i++)
    //    cout << step[i] << " "; cout << endl;
    //for(uint32_t i = 0; i <= n; i++)
    //    cout << int(group[i]) << " "; cout << endl;

    vector<query_t> queries(q);
    for(uint32_t i = 0; i < q; i++)
    {
        cin >> queries[i].t >> queries[i].L >> queries[i].R;
        queries[i].i = i;
    }
    sort(queries.begin(), queries.end(), [&](const query_t& lhs, const query_t& rhs) {
         return make_pair(lhs.t, lhs.i) < make_pair(rhs.t, rhs.i);
    });
    segment_bush rtree(-(1<<30)+1, 1<<30);
    rtree.mut(-n, 0, 1);
    vector<uint32_t> result(q);
    uint32_t t = 0;
    for(uint32_t j = 0; j < q; j++)
    {
        uint32_t t1 = queries[j].t;
        //cout << "warp " << t << " -> " << t1 << endl;
        for(uint32_t i = 0; i <= n; i += group[i])
        {
            int64_t m1 = himul((uint64_t)t1, step[i]), m = himul((uint64_t)t, step[i]);
            //cout << "move? " << i << " " << m << " " << m1 << endl;
            if(m1 > m)
            {
                //cout << " + " << endl;
                rtree.mut(m - i - group[i] + 1, m - i, -1);
                rtree.mut(m1 - i - group[i] + 1, m1 - i, 1);
            }
            else
                break;
        }
        result[queries[j].i] = rtree.get(queries[j].L, queries[j].R);
        t = t1;
    }
    for(uint32_t j = 0; j < q; j++)
        cout << result[j] << "\n";
}
