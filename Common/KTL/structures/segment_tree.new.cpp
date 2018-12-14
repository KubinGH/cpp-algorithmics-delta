// Segment trees with pretty flexible templates.
// Operations are provided as functors.

// Last revision: December 2018

#include <vector>
#include <cstddef>
#include <ext/functional>

using std::vector;
using std::size_t;
using __gnu_cxx::identity_element;

// Segment tree
// Interval get, point set
/*
T - value type
ChildrenOp - functor type, operator()(T, T) and identity_element(ChildrenOp) defined,
             used for calculating parent value from children.
*/
template<typename T, typename ChildrenOp>
struct segment_tree
{
    vector<T> values;
    size_t w;
    ChildrenOp F;
    segment_tree(size_t n, ChildrenOp f = {})
    {
        F = move(f);
        w = (31 - __builtin_clz(2*n-1));
        values.resize(2*w, identity_element(F));
    }
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value; i /= 2;
        while(i) values[i] = F(values[2*i], values[2*i+1]), i /= 2;
    }
    void get(size_t getL, size_t getR)
    {
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
};


// Segment tree
// Interval get, interval mutate
/*
T - value type
ChildrenOp - functor type, operator()(T, T) and identity_element(ChildrenOp) defined,
             used for calculating parent value from children
MT - mutate type
MutateOp - functor type, operator()(size_t, size_t, size_t, vector<T>, vector<MT>) and identity_element(MutateOp) defined,
           used for pulling down mutations from parent to children
MergeOp - functor type, operator()(MT, MT) defined,
          used for merging two mutations
*/

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
