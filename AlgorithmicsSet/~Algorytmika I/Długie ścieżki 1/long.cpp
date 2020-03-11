#include <bits/stdc++.h>
#include <ext/numeric>
#pragma GCC optimize ("unroll-loops")
#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("expensive-optimizations")

using namespace std;
using __gnu_cxx::power;

constexpr size_t N = 20;
constexpr size_t P = 13;
const char* B16 = "0123456789ABCDEF";

struct generator
{
    size_t n;
    uint64_t S, A, B, L;
    generator(size_t _n, uint64_t s, uint64_t a, uint64_t b, uint64_t l)
        : n(_n), S(s), A(a), B(b), L(l) {}
    uint64_t rand()
    {
        return S = S*A + B;
    }
    auto next_query()
    {
        // bez zmiennych tymczasowych kolejnosc jest zla :o
        uint64_t r1 = rand(), r2 = rand(), r3 = rand();
        return make_tuple(size_t(r1 % n), size_t(r2 % n), r3 % L);
    }
};

struct adjmatrix
{
    uint32_t masks[N] = {};
    inline void set(size_t i, size_t j)
    {
        masks[i] |= 1 << j;
    }
    inline void unset(size_t i, size_t j)
    {
        constexpr size_t full = (1 << N) - 1;
        masks[i] &= full ^ (1 << j);
    }
    adjmatrix T() const
    {
        adjmatrix t;
        for(size_t i = 0; i < N; i++)
            for(size_t j = 0; j < N; j++)
                if(masks[i] >> j & 1)
                    t.set(j, i);
        return t;
    }
};

adjmatrix operator* (const adjmatrix& A, const adjmatrix& B)
{
    adjmatrix C;
    auto Bt = B.T();
    for(size_t i = 0; i < N; i++)
        for(size_t j = 0; j < N; j++)
            if(A.masks[i] & Bt.masks[j])
                C.set(i, j);
    return C;
}
uint32_t operator* (const adjmatrix& A, uint32_t v)
{
    uint32_t w = 0;
    for(size_t i = 0; i < N; i++)
        if(A.masks[i] & v)
            w |= (1 << i);
    return w;
}

adjmatrix identity_element(multiplies<adjmatrix>)
{
    adjmatrix I;
    for(size_t i = 0; i < N; i++)
        I.set(i, i);
    return I;
}
const auto Id = identity_element(multiplies<adjmatrix>{});

int main()
{
    size_t n, m;
    cin >> n >> m;

    adjmatrix A;
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        A.set(u, v);
    }

    static adjmatrix powieA[(64+P-1)/P][1 << P];
    for(size_t e = 0; e < 64; e += P)
    {
        powieA[e/P][0] = Id;
        powieA[e/P][1] = power(A, (uint64_t)1 << e);
        for(size_t p = 2; p < (1u << P); p++)
            powieA[e/P][p] = powieA[e/P][p-1] * powieA[e/P][1];
    }

    size_t q; uint64_t gS, gA, gB, gL;
    cin >> q >> gS >> gA >> gB >> gL;
    generator gen(n, gS, gA, gB, gL);

    static char buffer[1 << 24];
    size_t buffer_i = 0;
    int curr = 0;

    for(size_t i = 0; i < q; i++)
    {
        auto [u, v, k] = gen.next_query();

        auto V = (1 << v);
        for(size_t e = 0; e < 64; e += P, k >>= P)
            V = powieA[e/P][k & ((1<<P)-1)] * V;

        auto ret = (V & (1 << u)) >> u;
        curr <<= 1;
        curr |= ret;
        if((q-i-1) % 4 == 0)
        {
            if(curr or buffer_i)
                buffer[buffer_i++] = B16[curr];
            curr = 0;
        }
    }
    if(not buffer_i)
        buffer[buffer_i++] = B16[0];

    fputs_unlocked(buffer, stdout);
}
