#include <bits/stdc++.h>
#include <ext/functional>

using namespace std;
using __gnu_cxx::identity_element;

const int64_t oo = 1LLU << 62;

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
    size_t find_dominant()
    {
        size_t i = 1, nodeL = 0, nodeR = w-1;
        pull(i, nodeL, nodeR);
        while(i < w)
        {
            uint32_t mid = (nodeL+nodeR)/2;
            pull(2*i, nodeL, mid);
            pull(2*i+1, mid+1, nodeR);
            if(values[i] == values[2*i])
                i *= 2, nodeR = mid;
            else
                i *= 2, i++, nodeL = mid+1;
        }
        return i - w;
    }
};

struct min_i64
{
    int64_t operator() (int64_t a, int64_t b) { return a<b ? a : b; }
};
int64_t identity_element(min_i64) { return oo; }
struct apply_add1
{
    void operator() (size_t i, size_t nodeL, size_t nodeR,
                     vector<int64_t>& values, vector<int64_t>& mutate)
    {
        values[i] += mutate[i];
        if(nodeL < nodeR)
        {
            mutate[2*i]   += mutate[i];
            mutate[2*i+1] += mutate[i];
        }
        mutate[i] = 0;
    }
};
int64_t identity_element(apply_add1) { return 0; }

typedef segment_tree_i<
    int64_t, min_i64,
    int64_t, apply_add1, plus<int64_t>
> minadd_bush;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<int64_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    minadd_bush T(n);
    int64_t s = 0;
    for(uint32_t i = n; i --> 0; )
    {
        s += A[i];
        T.mut(i, i, -oo + s + i * A[i]);
    }
    vector<bool> D(n);
    vector<int64_t> R(n+1);
    for(uint32_t i = 0; i < n; i++)
        R[n] += (i + 1) * A[i];
    for(uint32_t k = n; k --> 0; )
    {
        uint32_t i = T.find_dominant();
        int64_t v = T.get(i, i);
        D[i] = true;
        R[k] = R[k+1] - v;
        T.mut(i, i, -v + oo);
        if(i>0) T.mut(0, i-1, -A[i]);
        for(uint32_t j = i+1; j < n; j++)
            if(not D[j]) T.mut(j, j, -A[j]);
    }
    for(uint32_t k = 1; k <= n; k++)
        cout << R[k] << " ";
}
