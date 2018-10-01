#pragma once

#include <cstddef>
using std::size_t;

// Matrix implementation.
// Any-size O(n^3) multiplication.
// TODO: Remove the templates. Useful, but probably all of this can be
//       dynamic and with some macro-controlled asserts.

template<typename T, size_t W, size_t H, T MOD = 0>
struct matrix
{
    T A[W*H];
    size_t w = W, h = H;
    matrix(size_t w, size_t h) : w(w), h(h) { fill(A, A+w*h, 0); }
    matrix() : matrix(W, H) {}
    template<size_t AW, size_t AH, typename IT>
    matrix(const IT(&Q)[AH][AW])
    {
        w = AW; h = AH;
        for(size_t y = 0; y < AH; y++)
            for(size_t x = 0; x < AW; x++)
                (*this)(x, y) = T(Q[y][x]);
    }
    T& operator() (size_t x, size_t y) { return A[w*y+x]; }
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
            for(size_t i = 0; i < W; i++)
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
};
