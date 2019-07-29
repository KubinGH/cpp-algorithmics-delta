// Manacher's palindrome-finding algorithm.
// Returns a vector of both odd and even palindromes
// (in a spliced manner: odd/even/odd/even...)

// Last revision: July 2019

#pragma once

#include <algorithm>
#include <iterator>
#include <cstddef>
#include <limits>
#include <string>
#include <vector>

using std::vector; using std::string; using std::size_t;
using std::min;
using std::iterator_traits; using std::numeric_limits;

template<typename Iterator, typename T = typename iterator_traits<Iterator>::value_type>
vector<size_t> manacher(Iterator first, Iterator last, T leaf = numeric_limits<T>::max())
{
    size_t n = distance(first, last);
    vector<T> S(2*n+1);
    for(size_t i = 0; i < n; i++, ++first)
        S[2*i] = leaf, S[2*i+1] = *first;
    S[2*n] = leaf;
    n = 2*n + 1;
    vector<size_t> R(n);
    size_t m = 0;
    for(size_t i = 1; i+1 < n; i++)
    {
        if(i < 2*m and i < m+R[m])
            R[i] = min(R[2*m - i], m+R[m] - i);
        while(i > R[i] and i+R[i] < n-1 and S[i-R[i]-1] == S[i+R[i]+1])
            R[i]++;
        if(i + R[i] > m + R[m])
            m = i;
    }
    for(size_t i = 0; i < n; i++)
        R[i] = (R[i]+1) / 2;
    R.erase(R.begin()); R.pop_back();
    return R;
}
