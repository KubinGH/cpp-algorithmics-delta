// Jakub Bachurski
// Cukiernia - O(n 2^K) (K = 3)

#include <bits/stdc++.h>

using namespace std;

const int64_t oo = INT64_MAX/3;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    array<int64_t, 8> A;
    A.fill(+oo); A[0] = 0;
    size_t exist = 0;

    for(size_t i = 0; i < n; i++)
    {
        int64_t c[3];
        cin >> c[0] >> c[1] >> c[2];
        auto s = c[0] + c[1] + c[2];

        for(size_t k = 0; k < 3; k++)
            if(c[k])
                exist |= 1 << k;

        array<int64_t, 8> B;
        B.fill(+oo);
        for(size_t mask = 0; mask < 8; mask++)
          for(size_t k = 0; k < 3; k++)
            if(mask >> k & 1)
              B[mask] = min(B[mask], min(A[mask ^ (1 << k)], A[mask]) + s - c[k]);
        A = B;
    }

    cout << A[exist] << '\n';
}
