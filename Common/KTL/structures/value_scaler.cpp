#pragma once

#include <cstddef>
#include <unordered_map>
using std::size_t;
using std::unordered_map;

// Value scaler
// Map-based instead of overwrite
template<typename T, size_t N>
struct value_scaler
{
    T _A[N];
    unordered_map<T, size_t> M;
    template<typename Iterator>
    value_scaler(Iterator begin, Iterator end)
    {
        size_t n = 0;
        for(auto it = begin; it != end; it++)
            _A[n] = *it, n++;
        sort(_A, _A + n);
        M.reserve(2*n);
        for(size_t i = 0, f = 0; i < n; i++)
        {
            if(i > 0 and _A[i-1] == _A[i])
                f++;
            M[_A[i]] = i - f;
        }
    }
    const size_t& operator[] (const T& x)
    {
        return M[x];
    }
};
