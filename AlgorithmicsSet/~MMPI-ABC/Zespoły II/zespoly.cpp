#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, 4> A;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t c;
        cin >> c;
        A[c]++;
    }
    uint32_t result = 0, taken = 0;
    bool done = false;
    while(not done)
    {
        done = true;
        if(A[1] and A[3])
        {
            taken = min(A[1], A[3]);
            result += taken;
            A[1] -= taken; A[3] -= taken;
            done = false;
        }
        if(A[2] > 1)
        {
            taken = A[2] / 2;
            result += taken;
            A[2] -= 2 * taken;
            done = false;
        }
        if(A[1] and A[2])
        {
            taken = min(A[1], A[2]);
            A[3] += taken;
            A[1] -= taken; A[2] -= taken;
            done = false;
        }
        else if(A[1] > 1)
        {
            taken = A[1] / 2;
            A[2] += taken;
            A[1] -= taken * 2;
            done = false;
        }
    }
    cout << result;
}
