#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n;
    cin >> n;
    vector<pair<uint32_t, uint32_t>> B(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> B[i].first, B[i].second = i;
    sort(B.begin(), B.end());
    vector<uint32_t> A(n+2);
    uint32_t maxA;
    {
        uint32_t f = 0;
        for(uint32_t i = 0; i < n; i++)
        {
            if(i and B[i].first == B[i-1].first)
                f++;
            A[B[i].second+1] = i - f + 1;
        }
        maxA = n - f + 1;
    }
    A[0] = maxA; A[n+1] = 0;
    uint32_t r = 0;
    for(uint32_t a = 1; a <= n; a++)
      for(uint32_t b = a; b <= n; b++)
    {
        swap(A[a], A[b]);
        uint32_t c = 0;
        for(uint32_t i = 1; i <= n; i++)
        {
            if(A[i] > A[i-1])
                c++;
            else
                c = 1;
            r = max(r, c);
        }
        swap(A[a], A[b]);
    }
    cout << r;
}
