#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7, INV3 = 333333336;

template<typename T>
struct matrix
{
    size_t h, w;
    vector<T> A;
    bool is_identity = false;
    matrix() : h(0), w(0), is_identity(true) {}
    matrix(size_t _w, size_t _h) : h(_h), w(_w), A(w*h) {}
    matrix(const vector<vector<T>>& a) : h(a.size()), w(a[0].size()), A(w*h)
    {
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
            const size_t d = A.w;
            matrix<T> C(B.w, A.h);
            for(size_t i = 0; i < C.h; i++)
              for(size_t j = 0; j < C.w; j++)
            {
                T c = 0;
                for(size_t k = 0; k < d; k++)
                    c += A(i, k) * B(k, j);
                C(i, j) = c % MOD;
            }
            return C;
        }
    };
    template<typename T>
    matrix<T> identity_element(multiplies<matrix<T>>) { return matrix<T>{}; }
}

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
    void rget(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, vector<size_t>& out)
    {
        if(getL <= nodeL and nodeR <= getR)
            out.push_back(i);
        else if(nodeR < getL or getR < nodeL)
            return;
        else
        {
            rget(2*i, nodeL, (nodeL+nodeR)/2, getL, getR, out);
            rget(2*i+1, (nodeL+nodeR)/2+1, nodeR, getL, getR, out);
        }
    }
    vector<size_t> rget(size_t getL, size_t getR)
    {
        vector<size_t> out;
        rget(1, 0, w - 1, getL, getR, out);
        return out;
    }
};

using matrixtree = segment_tree<
    matrix<uint64_t>, multiplies<matrix<uint64_t>>
>;

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
        forms[f] = matrix<uint64_t>(4, 4);
        for(size_t i = 0; i < 4; i++)
            for(size_t j = 0; j < 4; j++)
                forms[f](i, j) = (i == j or j == f);
    }
    matrixtree T(n);
    for(size_t i = 0; i < n; i++)
        T.values[T.w+i] = forms[form(S[i])];
    for(size_t i = T.w; i --> 1; )
        T.values[i] = T.F(T.values[2*i], T.values[2*i+1]);

    matrix<uint64_t> ext(vector<vector<uint64_t>>{
        vector<uint64_t>{1, 1, 1, 1}
    });

    while(q --> 0)
    {
        size_t x, y;
        cin >> x >> y; x--; y--;
        auto I = T.rget(x, y);
        auto M = ext;
        for(auto m : I)
            M = T.F(M, T.values[m]);
        auto s = (M(0, 0) + M(0, 1) + M(0, 2) + M(0, 3)) % MOD;
        cout << (MOD + s - 4) * INV3 % MOD << endl;
    }
}
