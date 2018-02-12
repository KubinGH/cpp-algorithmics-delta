#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static array<uint32_t, MAX> A;
    cin >> A[0];
    uint32_t tbegin = 0, tend = 1, sum = A[0], result = -1u;
    if(sum >= k)
    {
        cout << 1; return 0;
    }
    for(uint32_t i = 1; i < n; i++)
    {
        cin >> A[i];
        sum += A[i], tend++;
        if(sum >= k)
        {
            while(sum - A[tbegin] >= k and tbegin + 1 < tend)
                tbegin++;
            result = min(result, tend - tbegin);
        }
    }
    if(result == -1u)
        cout << "NIE";
    else
        cout << result;
}
