#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

constexpr size_t N = 104;

struct adjmatrix
{
    bitset<N> masks[N] = {};
    adjmatrix T() const
    {
        adjmatrix t;
        for(size_t i = 0; i < N; i++)
            for(size_t j = 0; j < N; j++)
                if(masks[i][j])
                    t.masks[j][i] = true;
        return t;
    }
};

adjmatrix operator* (const adjmatrix& A, const adjmatrix& B)
{
    adjmatrix C;
    auto Bt = B.T();
    for(size_t i = 0; i < N; i++)
        for(size_t j = 0; j < N; j++)
            if((A.masks[i] & Bt.masks[j]).any())
                C.masks[i].set(j);
    return C;
}
bitset<N> operator* (const adjmatrix& A, const bitset<N>& v)
{
    bitset<N> w = {};
    for(size_t i = 0; i < N; i++)
        if((A.masks[i] & v).any())
            w.set(i);
    return w;
}

adjmatrix identity_element(multiplies<adjmatrix>)
{
    adjmatrix I;
    for(size_t i = 0; i < N; i++)
        I.masks[i].set(i);
    return I;
}
const auto Id = identity_element(multiplies<adjmatrix>{});

template<typename T, typename Fun>
T binary_search_bool(T lo, T hi, Fun f)
{
    while(lo < hi)
    {
        auto mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid+1;
    }
    return lo;
}

template<typename T, typename Fun>
void for_each_one_bit(T x, Fun f)
{
    for(size_t i = 0; i < numeric_limits<T>::digits; i++, x >>= 1)
        if(x & 1)
            f(i);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    adjmatrix A;
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        A.masks[u][v] = true;
    }

    A.masks[n][0] = true;
    A.masks[n+1][n+1] = true;

    static adjmatrix P2[N][64];
    for(size_t v = 0; v < n; v++)
    {
        A.masks[v][n+1] = true;
        P2[v][0] = A;
        A.masks[v][n+1] = false;
        for(size_t i = 1; i < 64; i++)
            P2[v][i] = P2[v][i-1] * P2[v][i-1];
    }
    static adjmatrix Q2[64];
    Q2[0] = A;
    for(size_t i = 1; i < 64; i++)
        Q2[i] = Q2[i-1] * Q2[i-1];

    bitset<N> T = {};
    T.set(n+1);

    while(q --> 0)
    {
        size_t v; uint64_t l;
        cin >> v >> l; v--;

        auto k_max = binary_search_bool<uint64_t>(0, l+1, [&](size_t k) {
            // none in [k, l]?
            auto V = T;
            for_each_one_bit(l - k + 1, [&](size_t i) {
                V = P2[v][i] * V;
            });
            for_each_one_bit(k + 1, [&](size_t i) {
                V = Q2[i] * V;
            });
            return not V[n];
        });

        if(k_max)
            cout << k_max-1 << '\n';
        else
            cout << "NIE\n";
    }
}
