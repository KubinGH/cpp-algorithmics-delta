#include <bits/stdc++.h>

using namespace std;

template<typename T, size_t W, size_t H, T MOD = 0>
struct matrix
{
    T A[W*H];
    size_t w = W, h = H;
    matrix(size_t w, size_t h) : w(w), h(h) { fill(A, A+w*h, 0); }
    matrix() : matrix(W, H) {}
    template<size_t AW, size_t AH>
    matrix(const T(&Q)[AH][AW])
    {
        w = AW; h = AH;
        for(size_t y = 0; y < AH; y++)
            for(size_t x = 0; x < AW; x++)
                (*this)(x, y) = T(Q[y][x]);
    }
    const T& operator() (size_t x, size_t y) const { return A[w*y+x]; }
    T& operator() (size_t x, size_t y) { return A[w*y+x]; }
    const T& operator[] (size_t i) const { return A[i]; }
    T& operator[] (size_t i) { return A[i]; }
    template<size_t L>
    matrix<T, L, H, MOD> operator* (matrix<T, L, W, MOD>& o)
    {
        matrix<T, L, H, MOD> r(o.w, h);
        for(size_t x = 0; x < o.w; x++)
          for(size_t y = 0; y < h; y++)
            for(size_t i = 0; i < max(w, o.h); i++)
        {
            r(x, y) += (*this)(i, y) * o(x, i);
            if(MOD != 0)
                r(x, y) %= MOD;
        }
        return r;
    }
    matrix& operator*= (matrix& o)
        { return (*this = operator*(o)); }
    template<typename PT>
    matrix<T, W, H, MOD> operator^ (PT p)
    {
        matrix<T, W, H, MOD> r, a;
        if(p > 0)
            r = a = *this, p--;
        else
        {
            for(uint32_t i = 0; i < W; i++)
                r(i, i) = 1;
            return r;
        }
        while(p)
        {
            if(p % 2 == 1)
                r *= a;
            p /= 2;
            a *= a;
        }
        return r;
    }
    template<typename PT>
    matrix& operator^= (PT p)
        { return (*this = operator^(p)); }
    void print() const
    {
        cout << "{\n  ";
        for(uint32_t y = 0; y < h and cout << "\n    "; y++)
            for(uint32_t x = 0; x < w; x++)
                cout << (*this)(x, y) << " ";
        cout << "\n}\n";
    }
};


int main()
{
    int64_t x;
    cout << "x = "; cin >> x;
    matrix<int64_t, 3, 3> M({{4*x*x, 1ll, -4*x}, {1ll, 0ll, 0ll}, {2*x, 0ll, -1ll}});
    matrix<int64_t, 1, 3> V({{1ll}, {x*x}, {x}});
    for(uint32_t i = 0; i < 16; i++)
    {
        auto P = (M^i); auto A = (M^i) * V;
        cout << "a(" << i << ")^2 = " << A(0, 1) << " " << A(0, 2) << endl;
    }
}
