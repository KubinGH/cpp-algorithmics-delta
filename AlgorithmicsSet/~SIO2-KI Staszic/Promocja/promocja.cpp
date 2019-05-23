#include <bits/stdc++.h>

using namespace std;

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
        size_t i = 0;
        for(const auto& o : a)
            for(const auto& x : o)
                A[i++] = x;
    }
    T& operator() (size_t i, size_t j) { return A[w*i + j]; }
    const T& operator() (size_t i, size_t j) const { return A[w*i + j]; }
};

void matrix_minsum_mul (const matrix<unsigned>& A, const matrix<unsigned>& B, matrix<unsigned>& C)
{
    if(A.is_identity) { C = B; return; }
    if(B.is_identity) { C = A; return; }
    const size_t d = A.w;
    for(size_t i = 0; i < C.h; i++)
      for(size_t j = 0; j < C.w; j++)
    {
        unsigned v = -1u;
        for(size_t k = 0; k < d; k++)
            v = min(v, A(i, k) + B(k, j));
        C(i, j) = v;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, kax, q;
    cin >> n >> kax >> q;

    const size_t m = kax + n;
    const size_t w = 1 << __lg(2*m - 1);
    vector<matrix<unsigned>> T(2*w);
    matrix<unsigned> base(n, n);
    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < n; j++)
            cin >> base(i, j);
    for(size_t p = 0; p < w; p++)
        T[w + p] = base;
    for(size_t p = w; p --> 1; )
    {
        T[p] = matrix<unsigned>(n, n);
        matrix_minsum_mul(T[2*p], T[2*p+1], T[p]);
    }

    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == 'Q')
        {
            size_t a, b;
            cin >> a >> b; a--; b--;
            cout << T[1](a, b) << "\n";
        }
        else if(c == 'U')
        {
            size_t k;
            cin >> k; k--;
            size_t p = w + k;
            for(size_t i = 0; i < n; i++)
                for(size_t j = 0; j < n; j++)
                    cin >> T[p](i, j);
            while(p > 1)
                p /= 2, matrix_minsum_mul(T[2*p], T[2*p+1], T[p]);
        }
    }
}
