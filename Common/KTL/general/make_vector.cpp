// Making multidimensional vectors in a human-readable way
// done during compile-time

// Last revision: March 2019

#pragma once

#include <vector>
#include <cstdint>

using std::vector;
using std::size_t;

template<typename T, size_t D>
struct vector_tag
{
    using type = vector<typename vector_tag<T, D - 1>::type>;
};

template<typename T>
struct vector_tag<T, 0>
{
    using type = T;
};

template<typename T>
vector<T> make_vector(size_t n)
{
    return vector<T>(n);
}

template<
    typename T, typename... Args,
    typename Result = typename vector_tag<T, sizeof...(Args) + 1>::type
>
Result make_vector(size_t n, Args... args)
{
    return Result(n, make_vector<T>(args...));
}
