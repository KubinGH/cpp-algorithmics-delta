#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<uint32_t> A(n);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];
    sort(A.begin(), A.end());
    uint32_t r = 0;
    for(size_t i = 0; i < n; i++)
      for(size_t j = i+1; j < n; j++)
    {
        if(A[i] + A[j] > m) continue;
        size_t k = upper_bound(A.begin() + j+1, A.end(), m - (A[i] + A[j]))
                    - A.begin();
        if(k == j+1)
            continue;
        r = max(r, A[i] + A[j] + A[k-1]);
    }
    cout << r;
}
