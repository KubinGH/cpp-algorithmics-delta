// Manacher's palindrome-finding algorithm.
// Returns a vector of both odd and even palindromes
// (in a spliced manner: odd/even/odd/even...)

// Last revision: Middle of 2018

#pragma once

#include <cstddef>
#include <string>
#include <vector>

using std::vector; using std::string; using std::size_t;

vector<uint32_t> manacher(const string& So, char leaf = '#')
{
    size_t n = So.size();
    vector<char> S(2*n+1);
    for(size_t i = 0; i < n; i++)
        S[2*i] = leaf, S[2*i+1] = So[i];
    S[2*n] = leaf;
    n = 2*n + 1;
    vector<size_t> R(n);
    size_t m = 0;
    for(size_t i = 1; i < n; i++)
    {
        if(i < 2*m and i < m+R[m])
            R[i] = min(R[2*m - i], m+R[m] - i);
        while(i > R[i] and i+R[i] < n-1 and S[i-R[i]-1] == S[i+R[i]+1])
            R[i]++;
        if(i + R[i] > m + R[m])
            m = i;
    }
    for(uint32_t i = 0; i < n; i++)
        R[i] = (R[i]+1) / 2;
    return R;
}
