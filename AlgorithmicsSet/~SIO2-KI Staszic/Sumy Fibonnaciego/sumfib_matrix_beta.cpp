#include <bits/stdc++.h>

using namespace std;

const int64_t RMOD = 1e9 + 7;

template<typename T>
struct matrix
{
    size_t w, h;
    vector<T> A;
    T mod;
    matrix(size_t _w, size_t _h, T _mod) : w(_w), h(_h), A(w*h), mod(_mod) {}
    template<typename QT>
    matrix(size_t _w, size_t _h, initializer_list<QT> Q, T _mod) : w(_w), h(_h), A(w*h), mod(_mod)
    {
        auto it = Q.begin();
        for(size_t i = 0; i < w*h; i++, it++)
            A[i] = *it;
    }
    static matrix identity(size_t n, size_t mod)
    {
        matrix o(n, n, mod);
        for(size_t i = 0; i < n; i++)
            o(i, i) = 1;
        return o;
    }
    T& operator() (size_t x, size_t y) { return A[y*w + x]; }
    matrix operator* (matrix& o)
    {
        matrix r(o.w, h, mod);
        assert(w == o.h);
        for(size_t y = 0; y < h; y++)
        {
            for(size_t x = 0; x < o.w; x++)
            {
                for(size_t k = 0; k < w; k++)
                {
                    r(x, y) += ((*this)(k, y) * o(x, k));
                    if(mod)
                        r(x, y) %= mod;
                }
            }
        }
        return r;
    }
    template<typename PT>
    matrix operator^ (PT p)
    {
        assert(w == h); size_t n = w;
        matrix r = matrix::identity(n, mod), a = *this;
        while(p)
        {
            if(p % 2)
                r = r * a;
            a = a * a;
            p /= 2;
        }
        return r;
    }
};

int main()
{
    matrix<int64_t> M(3, 3, {
        1, 0, 1,
        0, 0, 1,
        0, 1, 1
    }, RMOD);
    matrix<int64_t> A(1, 3, {
        0,
        0,
        1
    }, RMOD);
    int64_t a, b;
    cin >> a >> b;
    cout << ((M^b) * A)(0, 0) - ((M^(a-1)) * A)(0, 0);
}
