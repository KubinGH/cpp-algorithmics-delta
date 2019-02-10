#include <bits/stdc++.h>

using namespace std;

template<typename T, size_t W, size_t H>
struct matrix
{
    T A[W*H];
    size_t w = W, h = H;
    matrix(size_t w, size_t h) : w(w), h(h) { fill(A, A+w*h, T{}); }
    matrix() : matrix(W, H) {}
    template<size_t AW, size_t AH>
    matrix(const T(&Q)[AH][AW])
    {
        w = AW; h = AH;
        for(size_t y = 0; y < AH; y++)
            for(size_t x = 0; x < AW; x++)
                (*this)(x, y) = Q[y][x];
    }
    const T& operator() (size_t x, size_t y) const { return A[w*y+x]; }
    T& operator() (size_t x, size_t y) { return A[w*y+x]; }
    const T& operator[] (size_t i) const { return A[i]; }
    T& operator[] (size_t i) { return A[i]; }
    template<size_t L>
    matrix<T, L, H> operator* (const matrix<T, L, W>& o) const
    {
        matrix<T, L, H> r(o.w, h);
        for(size_t x = 0; x < o.w; x++)
          for(size_t y = 0; y < h; y++)
            for(size_t i = 0; i < max(w, o.h); i++)
        {
            r(x, y) += (*this)(i, y) * o(x, i);
        }
        return r;
    }
    matrix& operator*= (matrix& o)
        { return (*this = operator*(o)); }
    template<typename PT>
    matrix<T, W, H> operator^ (PT p)
    {
        matrix<T, W, H> r, a;
        if(p > 0)
            r = a = *this, p--;
        else
        {
            for(uint32_t i = 0; i < W; i++)
                r(i, i) = {1, 1};
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

struct fraction
{
    uint64_t a, b;
    fraction() : a(0), b(1) {}
    fraction(uint64_t a, uint64_t b) : a(a), b(b) {}
    fraction shortened() const
    {
        uint64_t d = __gcd(a, b);
        return {a / d, b / d};
    }
    fraction operator+ (const fraction& o) const
    {
        fraction r = fraction { o.b*a + b*o.a, b*o.b };
        return r.shortened();
    }
    fraction& operator+= (const fraction& o)
        { return *this = (*this + o); }
    fraction operator* (const fraction& o) const
    {
        fraction r = fraction { a * o.a, b * o.b };
        return r.shortened();
    }
    fraction operator%= (const fraction& o) const { (void)o; return *this; }
};

int main()
{
    vector<uint64_t> N;
    for(uint64_t n = 0; n < 32; n++)
    {
        matrix<fraction, 3, 3> M({ {{1, 2}, {1, 2}, {0, 1}},
                                   {{1, 2}, {0, 1}, {1, 2}},
                                   {{0, 1}, {1, 2}, {1, 2}} });
        matrix<fraction, 1, 3> S({ {{0, 1}}, {{1, 1}}, {{0, 1}} });
        matrix<fraction, 3, 3> P = (M^n);
        //for(uint32_t y = 0; y < 3; y++, cout << endl)
        //  for(uint32_t x = 0; x < 3; x++)
        //    cout << P(x, y).a << "/" << P(x, y).b << " ";
        matrix<fraction, 1, 3> R = P * S;
        //for(uint32_t y = 0; y < 3; y++, cout << endl)
        //  for(uint32_t x = 0; x < 1; x++)
        //    cout << R(x, y).a << "/" << R(x, y).b << " ";
        cout << n << ": " << R(0, 1).a << "/" << R(0, 1).b << endl;
        N.push_back(R(0, 1).a);
    }
    for(uint64_t i = 0; i < 16; i++)
        cout << N[i] << " "; cout << endl;
    for(uint64_t i = 2; i < 16; i++)
        cout << 3*(N[i] - N[i-1]) - 2 * pow(-1, i) << " "; cout << endl;
    cout << "1 0 ";
    for(uint64_t i = 2; i < 16; i++)
        cout << ((1 << (i-1)) + pow(-1, i))/3 << " "; cout << endl;
}

