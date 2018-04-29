#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 5e4, MAX_M = 1e6;

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    static pair<uint32_t, uint32_t> A[MAX_M];
    static uint32_t C[MAX_N], R[MAX_N];
    for(uint32_t i = 0; i < m; i++)
    {
        cin >> A[i].first >> A[i].second; A[i].first--; A[i].second--;
        C[A[i].first]++; R[A[i].second]++;
    }
    uint32_t r = 0;
    for(uint32_t i = 0; i < m; i++)
        if(C[A[i].first] == 1 and R[A[i].second] == 1)
            r++;
    cout << r;
}
