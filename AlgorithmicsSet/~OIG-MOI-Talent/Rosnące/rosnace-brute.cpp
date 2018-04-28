#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5;

int main()
{
    uint32_t n, z, f;
    cin >> n >> z >> f;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    int32_t r = 0;
    for(uint32_t k = 0; k <= n*f/z; k++)
    {
        uint32_t v = 1, mv = 1;
        for(uint32_t i = 1; i < n; i++)
        {
            if(A[i-1]+i*k < A[i]+(i+1)*k)
            {
                v++;
                mv = max(v, mv);
            }
            else v = 1;
        }
        r = max(r, (int32_t)(mv * f) - (int32_t)(k * z));
    }
    cout << r;
}
