#include <bits/stdc++.h>

using namespace std;

uint32_t log2floor(uint32_t n) { return 31 - __builtin_clz(n); }
uint32_t log2ceil (uint32_t n) { return log2floor(2*n+1); }
uint32_t min_u32(uint32_t a, uint32_t b) { return a<b ? a : b; }
template<typename T, T(*F)(T, T)>
struct power_tree
{
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator>
    power_tree(Iterator first, Iterator last)
    {
        n = distance(first, last);
        A.emplace_back(n);
        for(uint32_t i = 0; i < n; i++, first++)
            A[0][i] = *first;
        for(uint32_t p = 1; (1u << p) <= n; p++)
        {
            A.emplace_back(n - (1u << p) + 1);
            for(uint32_t i = 0; i <= n - (1u << p); i++)
                A[p][i] = F(A[p-1][i], A[p-1][i+(1u<<(p-1))]);
        }
    }
    T operator() (size_t x, size_t y) const
    {
        size_t p = log2floor(y - x + 1);
        return F(A[p][x], A[p][y + 1 - (1u << p)]);
    }
};

int main()
{
    uint32_t n; uint64_t p;
    cin >> n >> p;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    power_tree<uint32_t, min_u32> T(A.begin(), A.end());
    uint64_t t = 0, s = 0;
    for(uint64_t j = 0; j < n; j++)
    {
        for(uint64_t i = 0; i <= j; i++)
        {
            t += T(i, j);
            s += min((uint64_t)T(i, j), max((p + j - i) / (j - i + 1), 1llu) - 1);
        }
    }
    cout << t - s;
}
