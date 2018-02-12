#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 300000;

int main()
{
    ios_base::sync_with_stdio(false);
    uint32_t n, q;
    cin >> n >> q;
    vector<uint64_t> A;
    uint64_t c;
    cin >> c;
    A.push_back(c);
    uint64_t least = A[0];
    for(uint32_t i = 1; i < n; i++)
    {
        cin >> c;
        if(c < least)
        {
            A.push_back(c);
            least = c;
        }
    }
    n = A.size();
    for(uint32_t qi = 0; qi < q; qi++)
    {
        cin >> c;
        uint32_t i = n - (upper_bound(A.rbegin(), A.rend(), c) - A.rbegin());
        while(c and c >= A[n-1] and i < n)
        {
            if(c >= A[i])
            {
                c %= A[i];
                i = n - (upper_bound(A.rbegin(), A.rend(), c) - A.rbegin());
            }
            else i++;

        }
        cout << c << '\n';
    }
}
