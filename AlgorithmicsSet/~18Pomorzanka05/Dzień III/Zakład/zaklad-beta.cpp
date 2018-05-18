#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t B[MAX], C[MAX];
    uint64_t total = 0;
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i], total += B[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> C[i], total += C[i];
    uint64_t asum = total / (2*n);
    if(total % (2*n) != 0)
        goto fail;
    static uint32_t A[MAX];
    static uint32_t O[MAX][32], S[32];
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t t = (uint64_t)B[i] + (uint64_t)C[i] - asum;
        if(t % n != 0)
            goto fail;
        A[i] = t / n;
        for(uint32_t b = 0; b < 32; b++)
        {
            if(A[i] & (1u << b))
                O[i][b]++, S[b]++;
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t c = 0;
        for(uint32_t b = 0; b < 32; b++)
        {
            if(O[i][b])
                c += (1u << b) * n;
            else
                c += (1u << b) * S[b];
        }
        if(c != C[i])
            goto fail;
    }
    for(uint32_t i = 0; i < n; i++)
        cout << A[i] << " ";
    return 0;
fail:
    cout << -1;
}
