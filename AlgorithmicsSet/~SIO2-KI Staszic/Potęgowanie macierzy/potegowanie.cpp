#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100;

template<typename T, size_t W, size_t H, T MOD = 0>
struct matrix
{
    T A[W*H];
    size_t w = W, h = H;
    matrix(size_t w, size_t h) : w(w), h(h) { fill(A, A+w*h, 0); }
    matrix() : matrix(W, H) {}
    template<size_t AW, size_t AH>
    matrix(const T(&Q)[AW][AH])
    {
        size_t i = 0;
        w = AW; h = AH;
        for(size_t y = 0; y < AH; y++)
            for(size_t x = 0; x < AW; x++, i++)
                (*this)(x, y) = Q[i];
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
        matrix<T, W, H, MOD> r(w, h), a(w, h);
        if(p > 0)
            r = a = *this, p--;
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m; uint64_t n;
    cin >> m >> n;
    static matrix<uint64_t, MAX, MAX, uint64_t(1e9+7)> M(m, m);
    for(uint32_t y = 0; y < m; y++)
        for(uint32_t x = 0; x < m; x++)
            cin >> M(x, y);
    auto P = M ^ n;
    for(uint32_t y = 0; y < m; y++)
    {
        for(uint32_t x = 0; x < m; x++)
            cout << P(x, y) << " ";
        cout << "\n";
    }
}
