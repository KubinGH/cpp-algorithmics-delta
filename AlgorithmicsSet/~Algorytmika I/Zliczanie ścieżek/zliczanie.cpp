#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100;

template<typename T, size_t W, size_t H, T MOD = 0>
struct matrix
{
    T A[W*H];
    size_t w = W, h = H;
    matrix() { fill(A, A+W*H, 0); }
    matrix(const T(&Q)[W*H])
    {
        size_t i = 0;
        for(size_t y = 0; y < h; y++)
            for(size_t x = 0; x < w; x++, i++)
                (*this)(x, y) = Q[i];
    }
    T& operator() (size_t x, size_t y) { return A[w*y+x]; }
    T& operator[] (size_t i) { return A[i]; }
    template<size_t L>
    matrix<T, L, H, MOD> operator* (matrix<T, L, W, MOD>& o)
    {
        matrix<T, L, H, MOD> r;
        r.w = o.w; r.h = h;
        uint32_t l = o.w;
        for(size_t x = 0; x < l; x++)
          for(size_t y = 0; y < h; y++)
            for(size_t i = 0; i < w; i++)
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
        r.w = w; r.h = h; a.w = w; a.h = h;
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
            for(uint32_t x = 0; x < w; x++)
                cout << (*this)(x, y) << " ";
        }
        cout << "]" << endl;
    }
};

typedef matrix<uint64_t, MAX, MAX, uint64_t(1e9+7)> matrix_t;
typedef matrix<uint64_t, 1, MAX, uint64_t(1e9+7)> vector_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, z;
    cin >> n >> m >> z;
    static matrix_t graph;
    graph.w = n; graph.h = n;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph(u, v) = 1;
    }
    static matrix_t pows[64];
    pows[0] = graph;
    for(uint32_t i = 1; i < 64; i++)
        pows[i] = pows[i-1] * pows[i-1];
    for(uint32_t i = 0; i < z; i++)
    {
        uint32_t u, v; uint64_t k;
        cin >> u >> v >> k; u--; v--; k--;
        static vector_t vec;
        for(uint32_t y = 0; y < n; y++)
            vec(0, y) = graph(u, y);
        for(uint32_t i = 0; i < 64; i++)
        {
            if(k & (1llu << i))
                vec = pows[i] * vec;
        }
        cout << vec(0, v) << "\n";
    }
}
