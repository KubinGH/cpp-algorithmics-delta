#include <bits/stdc++.h>
#include <ext/numeric>
#define note(__val) #__val << " = " << (__val)

using namespace std;
using __gnu_cxx::power; using __gnu_cxx::identity_element;

const uint64_t MAX_NUMBER = 1llu << 60;

struct matrix
{
    bool is_identity = false;
    size_t n;
    vector<uint64_t> V;
    matrix() : n(0) {}
    matrix(size_t _n) : n(_n), V(n*n) {}
    static matrix universal_identity()
    {
        matrix M;
        M.is_identity = true;
        return M;
    }
    uint64_t& operator() (size_t i, size_t j) { return V[i*n + j]; }
    const uint64_t& operator() (size_t i, size_t j) const { return V[i*n + j]; }
};

matrix operator* (const matrix& A, const matrix& B)
{
    if(B.is_identity) return A;
    if(A.is_identity) return B;
    const size_t n = A.n;
    matrix C(n);
    for(size_t i = 0; i < n; i++)
     for(size_t j = 0; j < n; j++)
      for(size_t k = 0; k < n; k++)
    {
        uint64_t x = A(i, k) * B(k, j);
        if(C(i, j) == MAX_NUMBER or (A(i, k) != 0 and x / A(i, k) != B(k, j)) or
           C(i, j) + x > MAX_NUMBER)
            C(i, j) = MAX_NUMBER;
        else
            C(i, j) += x;
    }
    return C;
}

matrix identity_element(multiplies<matrix>) { return matrix::universal_identity(); }

int main()
{
    uint32_t n, m; uint64_t k;
    cin >> n >> m >> k;

    matrix G(3*n+1);

    for(uint32_t u = 0; u < n; u++)
        G(u+2*n, u+n)++, G(u+n, u)++, G(u, 3*n)++;
    G(3*n, 3*n)++;

    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--; v--;
        G(u, (w-1)*n + v)++;
    }

    vector<matrix> Q;
    Q.push_back(G);
    for(uint32_t i = 1; i < 63; i++)
        Q.push_back(Q.back() * Q.back());

    matrix P = G;

    auto count_valid = [&](const matrix& P_) {
        uint64_t valid = 0;
        for(uint32_t u = 0; u < n and valid < MAX_NUMBER; u++)
            valid += P_(u, 3*n) - 1;
        return valid;
    };

    uint64_t e = 0;
    for(uint32_t p = 63; p --> 0; )
    {
        auto P1 = P * Q[p];
        if(count_valid(P1) < k)
            P = P1, e += (1llu << p);
    }

    if(e == -1llu/2)
        cout << "-1";
    else
        cout << e+1;
}
