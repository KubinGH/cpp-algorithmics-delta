#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    vector<uint32_t> A(2*n-1);
    for(uint32_t i = 0; i < n; i++)
        A[2*i] = i + 1;
    for(uint32_t i = n; i --> 1; )
    {
        A[2*i-1] = A.back();
        A.pop_back();
    }
    while(q --> 0)
    {
        uint32_t i;
        cin >> i;
        cout << A[i-1] << "\n";
    }
}
