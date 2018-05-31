#include <bits/stdc++.h>

using namespace std;

const int64_t MOD = 1e9 + 7;

template<typename T, size_t W, size_t H, T MOD = 0>
struct matrix
{
    T A[W*H];
    matrix() { fill(A, A+W*H, 0); }
    matrix(const T(&Q)[W*H])
    {
        size_t i = 0;
        for(size_t y = 0; y < H; y++)
            for(size_t x = 0; x < W; x++, i++)
                (*this)(x, y) = Q[i];
    }
    T& operator() (size_t x, size_t y) { return A[W*y+x]; }
    T& operator[] (size_t i) { return A[i]; }
    template<size_t L>
    matrix<T, L, H, MOD> operator* (matrix<T, L, W, MOD>& o)
    {
        matrix<T, L, H, MOD> r;
        for(size_t x = 0; x < L; x++)
          for(size_t y = 0; y < H; y++)
            for(size_t i = 0; i < W; i++)
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
            r = a = *this;
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
    void print()
    {
        cout << "[" << endl;
        for(uint32_t y = 0; y < H; y++, cout << endl)
        {
            cout << " ";
            for(uint32_t x = 0; x < W; x++)
                cout << (*this)(x, y) << " ";
        }
        cout << "]" << endl;
    }
};

int64_t F(int64_t n)
{
    static matrix<int64_t, 2, 2, MOD> A({0, 1, 1, 1});
    if(n == 1) return 1;
    return (A^(n-1))(0, 1);
}

int main()
{
    int64_t a, b;
    cin >> a >> b;
    cout << (F(b+3) - F(a+2) + MOD) % MOD;
}
