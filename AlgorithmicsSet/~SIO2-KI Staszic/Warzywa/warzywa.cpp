#include <bits/stdc++.h>

using namespace std;

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
        for(uint32_t i = w; i < 2*w; i++)
            values[i] = initial_element(F);
        for(uint32_t i = w; i --> 1; )
            values[i] = F(values[2*i], values[2*i+1]);
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

typedef pair<uint32_t, uint32_t> pair_u32;

struct min_cnt
{
    pair_u32 operator() (pair_u32 a, pair_u32 b) const
    {
        if(a.first == b.first)
            return {a.first, a.second + b.second};
        else if(a.first < b.first)
            return a;
        else
            return b;
    }
};
pair_u32 identity_element(min_cnt) { return {0, 0}; }
pair_u32 initial_element(min_cnt) { return {0, 1}; }

struct add_to_min_cnt
{
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<pair_u32>& values,
                     vector<uint32_t>& mutate)
    {
        values[i].first += mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        mutate[i] = 0;
    }
};
uint32_t identity_element(add_to_min_cnt) { return 0; }


template<typename T>
void sort(array<T, 2>& p) { if(p[0] > p[1]) swap(p[0], p[1]); }
template<typename T>
T min(const set<T>& s) { return *s.begin(); }
template<typename T>
T max(const set<T>& s) { return *--s.end(); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<uint32_t> A(2*n+1);
    A[0] = -1u;
    vector<array<uint32_t, 2>> S(n, {-1u, -1u});
    set<uint32_t> segments[2];
    for(uint32_t i = 1; i <= 2*n; i++)
    {
        cin >> A[i]; A[i]--;
        if(S[A[i]][0] == -1u)
            S[A[i]][0] = i;
        else
            S[A[i]][1] = i;
    }
    set<uint32_t> begins0, ends0;
    segment_tree_i<
        pair_u32, min_cnt, uint32_t,
        add_to_min_cnt, plus<uint32_t>
    > union1_tree(2*n+1);
    auto count1 = [&](uint32_t i, uint32_t j) {
        auto c = union1_tree.get(i, j);
        return (j - i + 1) - (c.first == 0 ? c.second : 0);
    };
    auto add_segment = [&](uint32_t x) {
        if((S[x][1] - S[x][0])%2 == 0)
            begins0.insert(S[x][0]), ends0.insert(S[x][1]-1);
        else
            union1_tree.mut(S[x][0], S[x][1]-1, 1);
    };
    auto remove_segment = [&](uint32_t x) {
        if((S[x][1] - S[x][0])%2 == 0)
            begins0.erase(S[x][0]), ends0.erase(S[x][1]-1);
        else
            union1_tree.mut(S[x][0], S[x][1]-1, -1);
    };
    for(uint32_t x = 0; x < n; x++)
        add_segment(x);
    while(q --> 0)
    {
        uint32_t a, b;
        cin >> a >> b;
        remove_segment(A[a]); remove_segment(A[b]);
        uint32_t av = (S[A[a]][0] == a ? 0 : 1),
                 bv = (S[A[b]][0] == b ? 0 : 1);
        swap(S[A[a]][av], S[A[b]][bv]); swap(A[a], A[b]);
        sort(S[A[a]]); sort(S[A[b]]);
        add_segment(A[a]); add_segment(A[b]);
        array<uint32_t, 2> uni;
        if(begins0.empty() or ends0.empty())
            uni = {0, 2*n};
        else
            uni = {max(begins0), min(ends0)};
        if(uni[0] > uni[1])
            cout << "0\n";
        else
            cout << (uni[1] - uni[0] + 1) - count1(uni[0], uni[1]) << "\n";
    }
}
