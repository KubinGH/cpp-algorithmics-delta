#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX], B[MAX], C[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i];
    uint32_t M = 0;
    for(uint32_t i = 0; i < n; i++)
        cin >> C[i], M = max(M, C[i]);
    fill(A, A + n, 1);
    while(true) // O(M^n)
    {
        A[0]++;
        uint32_t i = 0;
        while(A[i] > M)
        {
            if(i == n - 1)
                goto after;
            A[i+1]++, A[i] -= M, i++;
        }
        for(uint32_t i = 0; i < n; i++)
        {
            uint32_t b = 0, c = 0;
            for(uint32_t j = 0; j < n; j++)
            {
                b += A[i] & A[j];
                c += A[i] | A[j];
            }
            if(b != B[i] or c != C[i])
                goto wrong;
        }
        for(uint32_t i = 0; i < n; i++)
            cout << A[i] << " ";
        return 0;
    wrong:;
    }
after:
    cout << -1;
}
