#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6, TMAX = (32 - __builtin_clz(MAX));

uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}
uint32_t min(uint32_t a, uint32_t b)
{
    return a < b ? a : b;
}

template<typename T>
T log2floor(T n)
{
    return numeric_limits<T>::digits - __builtin_clz(n);
}

template<typename T, T(*F)(T, T)>
struct interval_operator
{
    // Requires F(a, b) == F(F(a, b), b), and F(a, b) == F(b, a)
    // Examples: min, max, and, or
    size_t n, t;
    array<array<T, MAX>, TMAX> A;
    template<typename Iterator>
    interval_operator(Iterator tbegin, Iterator tend)
    {
        size_t i = 0;
        for(auto it = tbegin; it != tend; it++, i++)
            A[0][i] = *it;
        n = i;
        t = log2floor(n);
        for(size_t i = 1; i < t and (1u << i) <= n + 1; i++)
            for(size_t j = 0; j < n + 1 - (1 << i); j++)
                A[i][j] = F(A[i-1][j], A[i-1][j + (1u << (i-1))]);
    }
    T operator() (size_t a, size_t b)
    {
        uint32_t p = log2floor(b - a + 1) - 1;
        return F(A[p][a], A[p][b + 1 - (1 << p)]);
    }
};

int main()
{
    srand(time(0));
    uint32_t n = 20;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        A[i] = rand() % 32;
    static interval_operator<uint32_t, min> O(A.begin(), A.end());
    for(uint32_t i = 0; i < n; i++)
        cout << O.A[0][i] << " ";
    cout << endl;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = i; j < n; j++)
        {
            uint32_t m = -1u;
            for(uint32_t k = i; k <= j; k++)
                m = min(m, A[k]);
            if(O(i, j) != m)
            {
                cout << endl;
                cout << i << ".." << j << " " << O(i, j) << " " << m << endl;
                abort();
            }
            else
            {
                cout << i << ".." << j << " " << O(i, j) << endl;
            }
        }
    }
}
