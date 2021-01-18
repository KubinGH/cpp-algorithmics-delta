// Jakub Bachurski
// Cukiernia - O(n K^n) (K = 3)

#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    int exist = 0;
    vector<array<int64_t, 3>> A(n);
    for(auto& [a, b, c] : A)
        cin >> a >> b >> c;
    for(size_t i = 0; i < n; i++)
        for(size_t k = 0; k < 3; k++)
            if(A[i][k])
                exist |= 1 << k;

    vector<uint> pow3(n+1);
    pow3[0] = 1;
    for(size_t i = 0; i < n; i++)
        pow3[i+1] = pow3[i] * 3;
    auto trit_get = [&](size_t mask, size_t i) {
        return (mask / pow3[i]) % 3;
    };

    int64_t result = INT64_MAX;
    for(size_t mask = 0; mask < pow3[n]; mask++)
    {
        int take = 0; int64_t curr = 0;
        for(size_t i = 0; i < n; i++)
        {
            size_t l = trit_get(mask, i);
            curr += A[i][0] + A[i][1] + A[i][2] - A[i][l];
            take |= 1 << l;
        }
        if((exist & take) == exist)
            result = min(result, curr);
    }

    cout << result << endl;
}
