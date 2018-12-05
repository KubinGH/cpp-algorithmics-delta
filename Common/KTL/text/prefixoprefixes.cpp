#include <cstddef>
#include <cstdint>
#include <vector>

using std::size_t; using std::uint32_t;
using std::vector;

template<typename Iterator>
vector<uint32_t> prefixoprefixes(Iterator S, size_t n)
{
    vector<uint32_t> Z(n);
    uint32_t L = 0, R = 0;
    Z[0] = n;
    for(uint32_t i = 1; i < n; i++)
    {
        if(i <= R and Z[i-L] < R-i+1)
            Z[i] = Z[i-L];
        else
        {
            L = i;
            if(i > R) R = i;
            while(R < n and S[R-L] == S[R])
                R++;
            R--;
            Z[i] = R - L + 1;
        }
    }
    return Z;
}
