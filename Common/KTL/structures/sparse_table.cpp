// Sparse table - O(n log n) construction, O(1) queries.
// Note: memory usage is not optimized in this implementation
// Requires idempotency, commutativity and associativity
// [(a @ b) @ b = a @ b, a @ b = b @ a, (a @ b) @ c = a @ (b @ c) respectively]
// Examples: min, max, bit and, bit or

// Last revision: October 2018

#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>
#include <cstdint>

using std::size_t;
using std::vector;
using std::__lg;

template<typename T, typename BinaryOperation>
struct sparse_table
{
    struct _identity { T operator() (const T& x) const { return x; } };
    BinaryOperation F;
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator, typename TransformOperation = _identity>
    sparse_table(Iterator first, Iterator last, BinaryOperation f = {},
                 TransformOperation t = {}) : F(f)
    {
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
        size_t p = __lg(b - a);
        return F(A[p][a], A[p][b - (1 << p)]);
    }
};
