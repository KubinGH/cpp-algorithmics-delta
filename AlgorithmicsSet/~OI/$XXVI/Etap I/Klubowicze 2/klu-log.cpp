#include <bits/stdc++.h>

using namespace std;

template<typename T, typename BinaryOperation>
struct sparse_table
{
    constexpr uint32_t log2floor(uint32_t n)
        { return 31 - __builtin_clz(n); }
    struct _identity { T operator() (const T& x) const { return x; } };
    BinaryOperation F;
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator, typename TransformOperation = _identity>
    sparse_table(Iterator first, Iterator last, BinaryOperation f = {},
                 TransformOperation t = {})
    {
        F = move(f);
        n = distance(first, last);
        A.emplace_back(distance(first, last));
        for(size_t i = 0; first != last; first++, i++)
            A[0][i] = t(*first);
        for(size_t i = 1; (1u << i) <= n; i++)
        {
            A.emplace_back(n - (1u << i) + 1);
            for(size_t j = 0; j + (1 << i) <= n; j++)
                A[i][j] = F(A[i-1][j], A[i-1][j + (1u << (i-1))]);
        }
    }
    T operator() (size_t a, size_t b)
    {
        size_t p = log2floor(b - a + 1);
        return F(A[p][a], A[p][b + 1 - (1 << p)]);
    }
};

typedef sparse_table<uint32_t, bit_or<uint32_t>> or_table;

template<typename Arg, typename MonoOperation>
Arg first_true(Arg lo, Arg hi, MonoOperation f)
{
    while(lo < hi)
    {
        Arg mid = (lo + hi) / 2;
        if(f(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k, n;
    cin >> k >> n;
    vector<uint32_t> A(2*n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    copy(A.begin(), A.begin() + n, A.begin() + n);
    const uint32_t K = (1 << k) - 1;
    or_table X(A.begin(), A.end());
    or_table Y(A.begin(), A.end(), {}, [K](uint32_t x) { return x ^ K; });
    uint64_t r = 0;
    for(uint32_t a = 0, b = n; a < n; a++, b++)
    {
        uint32_t leftX, rightX, leftY, rightY;
        leftX = first_true(a, b-1, [&](uint32_t mid) {
            return X(a, mid) >= X(mid+1, b-1);
        });
        rightX = first_true(a, b-1, [&](uint32_t mid) {
            return X(a, mid) > X(mid+1, b-1);
        });
        leftY = first_true(a, b-1, [&](uint32_t mid) {
            return Y(a, mid) >= Y(mid+1, b-1);
        });
        rightY = first_true(a, b-1, [&](uint32_t mid) {
            return Y(a, mid) > Y(mid+1, b-1);
        });
        uint32_t left = max(leftX, leftY), right = min(rightX, rightY);
        if(left < right)
            r += right - left;
    }
    r /= 2;
    cout << r;
}
