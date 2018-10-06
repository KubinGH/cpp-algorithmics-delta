#include <bits/stdc++.h>

using namespace std;

template<typename T, typename ChildrenOp,
         typename MT, typename MutateOp, typename MergeOp>
struct segment_tree
{
    ChildrenOp F;
    MutateOp M;
    MergeOp S;
    size_t w;
    vector<T> values;
    vector<MT> mutate;
    segment_tree(size_t n, ChildrenOp f = {}, MutateOp m = {}, MergeOp s = {})
    {
        F = move(f); M = move(m); S = move(s);
        w = 1 << (31 - __builtin_clz(2*n-1));
        values.resize(2*w, F.identity);
        mutate.resize(2*w, M.identity);
    }
    void pull(size_t i, size_t nodeL, size_t nodeR)
    {
        M(i, nodeL, nodeR, values, mutate);
    }
    T get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        pull(i, nodeL, nodeR);
        if(nodeR < getL or nodeL > getR)
            return F.identity;
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

struct min_i32 {
    int32_t identity = INT32_MAX;
    int32_t operator() (int32_t a, int32_t b) { return a<b ? a : b; }
};
struct add_i32 {
    int32_t identity = 0;
    int32_t operator() (int32_t a, int32_t b) { return a+b; }
};
struct apply_minadd
{
    int32_t identity = 0;
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<int32_t>& values, vector<int32_t>& mutate)
    {
        values[i] += mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        mutate[i] = identity;
    }
};

typedef segment_tree<
    int32_t, min_i32, int32_t, apply_minadd, add_i32
> min_segment_tree;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    min_segment_tree tree(n);
    fill(tree.values.begin(), tree.values.end(), 0);
    vector<int32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t v;
        cin >> v;
        tree.mut(i, n-1, A[i] = v);
    }
    int32_t c;
    while(cin >> c)
    {
        if(c == -1) break;
        else if(c == 0)
            cout << (tree.get(0, n-1) >= 0 and tree.get(n-1, n-1) == 0 ? "TAK" : "NIE") << "\n";
        else
            tree.mut(c-1, n-1, 2*(A[c-1] *= -1));
    }
}
