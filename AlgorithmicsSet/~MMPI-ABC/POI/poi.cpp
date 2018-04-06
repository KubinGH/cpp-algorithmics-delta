#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, t, p;
    cin >> n >> t >> p; p--;
    static uint32_t V[MAX];
    static uint32_t D[MAX][MAX];
    static tuple<uint32_t, uint32_t, uint32_t> A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        get<2>(A[i]) = n - i;
        for(uint32_t j = 0; j < t; j++)
        {
            uint32_t d;
            cin >> d;
            D[i][j] = d;
            if(d)
                get<1>(A[i])++;
            else
                V[j]++;
        }
    }
    for(uint32_t i = 0; i < n; i++)
        for(uint32_t j = 0; j < t; j++)
            if(D[i][j])
                get<0>(A[i]) += V[j];
    sort(A, A + n);
    for(uint32_t i = 0, k = n; i < n; i++, k--)
    {
        if(get<2>(A[i]) == n - p)
        {
            cout << get<0>(A[i]) << " " << k;
            break;
        }
    }
}
