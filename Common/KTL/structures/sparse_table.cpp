#pragma once

#include <cstddef>
#include <vector>
#include <cstdint>

using std::size_t;
using std::vector;
using std::uint32_t; using std::uint64_t;

// Sparse table - O(n log n) construction, O(1) queries.
// Note: memory usage is not optimized in this implementation
// Requires F(a, b) == F(F(a, b), b), and F(a, b) == F(b, a)
// Examples: min, max, bit and, bit or

// WARNING: Untested after refactoring.

template<typename T, T(*F)(T, T)>
struct sparse_table
{
    constexpr uint32_t log2floor(uint32_t n)
        { return 31 - __builtin_clz(n); }
    constexpr uint32_t log2floor(uint64_t n)
        { return 63 - __builtin_clzll(n); }
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator>
    sparse_table(Iterator first, Iterator last)
    {
        n = distance(first, last);
        A.emplace_back(distance(first, last));
        for(size_t i = 0; first != last; first++, i++)
            A[0][i] = *first;
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
