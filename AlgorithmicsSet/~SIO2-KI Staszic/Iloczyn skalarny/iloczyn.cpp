#include <iostream>
#include <cstdint>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

template<typename A, typename B>
ostream& operator<< (ostream& out, const pair<A, B>& p)
{
    return out << "{" << p.first << ", " << p.second << "}";
}

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

struct tri_u64 { uint64_t a, b, s; };
typedef pair<uint64_t, uint64_t> pair_u64;

struct add_3u64 {
    tri_u64 identity {0, 0, 0};
    tri_u64 operator() (tri_u64 a, tri_u64 b)
        { return {(a.a+b.a), (a.b+b.b), (a.s+b.s)}; }

};
struct merge_sca {
    pair_u64 identity = {0, 0};
    pair_u64 operator() (pair_u64 a, pair_u64 b)
        { return {(a.first+b.first), (a.second+b.second)}; }
};
struct apply_sca {
    pair_u64 identity = {0, 0};
    merge_sca S;
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<tri_u64>& values, vector<pair_u64>& mutate)
    {
        size_t d = nodeR - nodeL + 1;
        values[i].s += (values[i].a * mutate[i].second);
        values[i].s += (values[i].b * mutate[i].first);
        values[i].s += (d * ((mutate[i].first * mutate[i].second)));
        values[i].a += d * mutate[i].first;
        values[i].b += d * mutate[i].second; 
        if(nodeL < nodeR)
        {
            mutate[2*i+0] = S(mutate[2*i+0], mutate[i]);
            mutate[2*i+1] = S(mutate[2*i+1], mutate[i]);
        }
        mutate[i] = identity;
    }
};

typedef segment_tree<
    tri_u64, add_3u64, pair_u64, apply_sca, merge_sca
> sca_segment_tree;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    sca_segment_tree tree(n, {}, {}, {});
    for(uint32_t i = 0; i < n; i++) { uint64_t x; cin >> x; tree.mut(i, i, {x, 0}); }
    for(uint32_t i = 0; i < n; i++) { uint64_t x; cin >> x; tree.mut(i, i, {0, x}); }
    while(q --> 0)
    {
        char c; uint32_t l, r; uint64_t x;
        cin >> c;
        if(c == '+') cin >> c;
        cin >> l >> r; l--; r--;
        if(c == 'a')
        {
            cin >> x;
            tree.mut(l, r, {x, 0});
        }
        else if(c == 'b')
        {
            cin >> x;
            tree.mut(l, r, {0, x});
        }
        else if(c == '?')
        {
            cout << tree.get(l, r).s << "\n";
        }
    }
}
