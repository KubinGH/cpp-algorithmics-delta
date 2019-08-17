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
    void set(size_t i, T value)
    {
        i += w;
        values[i] = value;
        while(i > 1)
            i /= 2, values[i] = F(values[2*i], values[2*i+1]);
    }
    T get(size_t getL, size_t getR)
    {
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
    T get() { return values[1]; }
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


// -*- ktl/ktl_debug_mode.cpp -*-

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

// -$- ktl/ktl_debug_mode.cpp -$-

// -*- ktl/math/matrix.cpp -*-

#include <algorithm>
#include <numeric>
#include <cstdint>
#include <vector>
#include <memory>

using std::size_t;
using std::vector;
using std::copy; using std::fill; using std::min;
using std::multiplies;
using std::numeric_limits;
using std::__lg;

template<typename T>
struct matrix
{
    size_t h, w;
    vector<T> A;
    bool is_identity = false;
    matrix() : h(0), w(0), is_identity(true) {}
    matrix(size_t _w, size_t _h) : h(_h), w(_w), A(w*h) {}
    matrix(const vector<vector<T>>& a) : h(a[0].size()), w(a.size()), A(w*h)
    {
        KTL_DEBUG_ASSERT(all_of(a.begin(), a.end(), [&](const vector<T>& v) { return v.size() == a[0].size(); }));
        size_t i = 0;
        for(const auto& o : a)
            for(const auto& x : o)
                A[i++] = x;
    }
    T& operator() (size_t i, size_t j) { return A[w*i + j]; }
    const T& operator() (size_t i, size_t j) const { return A[w*i + j]; }
};

namespace std
{
    template<typename T>
    struct multiplies<matrix<T>>
    {
        matrix<T> operator() (const matrix<T>& A, const matrix<T>& B)
        {
            if(A.is_identity) return B;
            if(B.is_identity) return A;
            KTL_DEBUG_ASSERT(A.w == B.h);
            const size_t d = A.w;
            matrix<T> C(B.w, A.h);
            for(size_t i = 0; i < C.h; i++)
                for(size_t j = 0; j < C.w; j++)
                    for(size_t k = 0; k < d; k++)
                        C(i, j) += A(i, k) * B(k, j);
            return C;
        }
    };
    template<typename T>
    matrix<T> identity_element(multiplies<matrix<T>>) { return matrix<T>(); }
}
template<typename T>
struct matrix_minsum_multiplies
{
    matrix<T> operator() (const matrix<T>& A, const matrix<T>& B)
    {
        if(A.is_identity) return B;
        if(B.is_identity) return A;
        KTL_DEBUG_ASSERT(A.w == B.h);
        const size_t d = A.w;
        matrix<T> C(B.w, A.h);
        for(size_t i = 0; i < C.h; i++)
          for(size_t j = 0; j < C.w; j++)
        {
            T v = numeric_limits<T>::max();
            for(size_t k = 0; k < d; k++)
                v = min(v, A(i, k) + B(k, j));
            C(i, j) = v;
        }
        return C;
    }
};
template<typename T>
matrix<T> identity_element(matrix_minsum_multiplies<T>) { return matrix<T>(); }

template<typename T, T Mod>
struct matrix_mod_multiplies
{
    matrix<T> operator() (const matrix<T>& A, const matrix<T>& B)
    {
        if(A.is_identity) return B;
        if(B.is_identity) return A;
        KTL_DEBUG_ASSERT(A.w == B.h);
        const size_t d = A.w;
        matrix<T> C(B.w, A.h);
        const size_t g = (1 << __lg(numeric_limits<T>::max() / (Mod*Mod) - 1)) - 1;
        for(size_t i = 0; i < C.h; i++)
            for(size_t j = 0; j < C.w; j++)
                for(size_t k = 0; k < d; k++)
        {
            C(i, j) += A(i, k) * B(k, j);
            if(((d-1 - k) & g) == 0)
                C(i, j) %= Mod;
        }
        return C;
    }
};
template<typename T, T Mod>
matrix<T> identity_element(matrix_mod_multiplies<T, Mod>) { return matrix<T>(); }

// -$- ktl/math/matrix.cpp -$-

#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7;

using matrixtree = segment_tree<
    matrix<uint64_t>, matrix_mod_multiplies<uint64_t, MOD>
>;

matrix<uint64_t> rget(matrixtree& T, size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
{
    if(getL <= nodeL and nodeR <= getR)
        return T.values[i];
    else if(nodeR < getL or getR < nodeL)
        return {};
    else
        return T.F(
            rget(T, 2*i, nodeL, (nodeL+nodeR)/2, getL, getR),
            rget(T, 2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR)
        );
}
matrix<uint64_t> rget(matrixtree& T, size_t getL, size_t getR)
{
    return rget(T, 1, 0, T.w - 1, getL, getR);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n, q;
    cin >> n >> q;

    string S;
    cin >> S;

    auto form = [](char c) {
        if(c == 'A')
            return 0;
        else if(c == 'C')
            return 1;
        else if(c == 'T')
            return 2;
        else if(c == 'G')
            return 3;
    };

    matrix<uint64_t> forms[4];
    for(size_t f = 0; f < 4; f++)
    {
        forms[f] = matrix<uint64_t>(5, 5);
        for(size_t i = 0; i < 5; i++)
            for(size_t j = 0; j < 5; j++)
                forms[f](i, j) = (i == j or j == f);
    }
    matrixtree T(n);
    for(size_t i = 0; i < n; i++)
        T.set(i, forms[form(S[i])]);

    matrix<uint64_t> ext({
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}
    });


    while(q --> 0)
    {
        size_t x, y;
        cin >> x >> y; x--; y--;
        auto M = T.F(ext, rget(T, x, y));
        cout << (M(0, 0) + M(0, 1) + M(0, 2) + M(0, 3)) % MOD << endl;
    }
}
