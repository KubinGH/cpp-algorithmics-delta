#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    cout.precision(1); cout.setf(ios_base::fixed);
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t k, n;
        cin >> k >> n;
        static array<uint64_t, MAX> A;
        for(uint32_t i = 0; i < n; i++)
            cin >> A[i];
        sort(A.begin(), A.begin() + n);
        float sum = 0;
        for(uint32_t i = 0; i < n; i++)
            A[i] -= sum, sum += A[i];
        A[0] = 0;
        float lo = 0, hi = sum;
        while(hi - lo > 0.01)
        {
            float x = (lo + hi) / 2, dx = 2 * x;
            uint32_t used = 1; uint64_t current = 0;
            for(uint32_t i = 0; i < n; i++)
            {
                if(current + A[i] <= dx)
                    current += A[i];
                else
                    current = 0, used++;
            }
            if(used <= k)
                hi = x;
            else
                lo = x + 0.01;
        }
        cout << lo << '\n';
    }
}
