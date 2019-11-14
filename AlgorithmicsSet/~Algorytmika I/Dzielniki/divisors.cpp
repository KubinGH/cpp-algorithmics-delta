#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const int64_t primes[] = {
      2,  3,  5,  7, 11, 13, 17, 19,
     23, 29, 31, 37, 41, 43, 47, 53,
     59, 61, 67, 71, 73, 79, 83, 89
};
const int64_t oo = 1e14;

int main()
{
    size_t n;
    cin >> n;

    vector<int64_t> A(n+1, +oo), B(n+1, +oo);
    A[1] = 1;
    for(auto p : primes)
    {
        swap(A, B);
        A = B;

        for(size_t x = 1; x <= n; x++)
            for(size_t k = 1; x*(k+1) <= n and power(p, k) < +oo; k++)
                if(B[x] < +oo/power(p, k) + 0xD)
                    A[x*(k+1)] = min(A[x*(k+1)], B[x]*power(p, k));
    }

    cout << A[n];
}
