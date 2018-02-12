#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;
const size_t MAX_E = 100000;

int main()
{
    uint32_t n;
    cin >> n;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint32_t r = 0;
    for(uint32_t tbegin = 0; tbegin < n; tbegin++)
    {
        static array<uint32_t, MAX_E> C;
        C.fill(0);
        uint32_t c = 0;
        for(uint32_t tend = tbegin+1; tend <= n; tend++)
        {
            C[A[tend-1]]++;
            if(C[A[tend-1]] == 1)
                c++;
            else if(C[A[tend-1]] == 2)
                c--;
            r = max(c, r);
        }
    }
    cout << r;
}
