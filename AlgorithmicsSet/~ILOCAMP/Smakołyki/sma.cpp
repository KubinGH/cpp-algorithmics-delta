#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    gp_hash_table<uint32_t, null_type> H;
    uint64_t r = 0;
    for(uint32_t i = 0, j = 1; j <= n; j++)
    {
        while(i < j and H.find(A[j-1]) != H.end())
            H.erase(A[i++]);
        H.insert(A[j-1]);
        r += j - i;
    }
    cout << r;
}
