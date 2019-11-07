#include <bits/stdc++.h>

// -*- ktl/structures/segment_tree.cpp -*-

#include <algorithm>
#include <vector>
#include <cstddef>
#include <ext/functional>

using std::vector;
using std::size_t;
using std::__lg;
using __gnu_cxx::identity_element;

template<typename T, typename ChildrenOp>
struct segment_tree
{
    vector<T> values;
    size_t w;
    ChildrenOp F;
    segment_tree(size_t n, ChildrenOp f = {}) : F(f)
    {
        w = 1 << __lg(2*n-1);
        values.resize(2*w, identity_element(F));
    }
    template<typename Iterator>
    segment_tree(Iterator first, Iterator last, ChildrenOp f = {}) : segment_tree(distance(first, last), f)
    {
        copy(first, last, values.begin() + w);
        for(size_t i = w; i --> 1; )
            values[i] = F(values[2*i], values[2*i+1]);
    }
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value;
        while(i > 1)
            i /= 2, values[i] = F(values[2*i], values[2*i+1]);
    }
    T get(size_t getL, size_t getR) const
    {
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
    T get() const { return values[1]; }
};

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
        : F(f), M(m), S(s)
    {
        w = 1 << __lg(2*n-1);
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
    T get() { return get(0, w-1); }
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

// -$- ktl/structures/segment_tree.cpp -$-


using namespace std;

const int64_t oo = INT64_MAX / 3;

struct minfun { int64_t operator() (int64_t a, int64_t b) { return min(a, b); } };

struct mutadd
{
    void operator() (size_t i, size_t nodeL, size_t nodeR, vector<int64_t>& values, vector<int64_t>& mutate)
    {
        values[i] += mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i] += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        mutate[i] = 0;
    }
};
int64_t identity_element(minfun) { return oo; }
int64_t identity_element(mutadd) { return 0; }

using tree = segment_tree_i<
    int64_t, minfun,
    int64_t, mutadd, plus<int64_t>
>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int64_t> A(n);
    for(int64_t& a : A)
        cin >> a;

    tree T(n);
    for(size_t i = 0; i < n; i++)
        T.mut(i, i, A[i] - oo);

    while(q --> 0)
    {
        char c;
        cin >> c;

        if(c == '+')
        {
            size_t l, r; int64_t v;
            cin >> l >> r >> v; l--; r--;
            T.mut(l, r, v);
        }
        else if(c == '?')
        {
            size_t l, r;
            cin >> l >> r; l--; r--;
            cout << T.get(l, r) << '\n';
        }
    }
}
