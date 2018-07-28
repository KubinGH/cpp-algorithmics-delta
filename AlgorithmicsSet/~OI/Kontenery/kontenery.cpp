#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5 + 4, MAX_ROOT = 317 + 4;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    uint32_t root = ceil(sqrt(n));
    static int32_t A[MAX], D[MAX_ROOT][MAX];
    while(k --> 0)
    {
        uint32_t a, c, d;
        cin >> a >> c >> d; a--;
        if(d > root)
        {
            for(uint32_t i = 0; i < c; i++)
                A[a + i*d]++;
        }
        else
        {
            D[d][a]++;
            if(a + c*d < n)
                D[d][a + c*d]--;
        }
    }
    for(uint32_t d = 1; d <= root; d++)
    {
        for(uint32_t i = 0; i < n; i++)
        {
            if(i >= d)
                D[d][i] += D[d][i-d];
            A[i] += D[d][i];
        }
    }
    for(uint32_t i = 0; i < n; i++)
        cout << A[i] << " ";
}
