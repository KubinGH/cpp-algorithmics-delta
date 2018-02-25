#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static array<vector<pair<uint32_t, uint32_t>>, MAX> A;
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t a, b, d;
        cin >> a >> b >> d;
        A[d].emplace_back(a, b);
    }
    for(uint32_t i = 1; i <= n; i++)
    {
        uint32_t rt = i >= 3 ? floor(sqrt(i)) : 1;
        cerr << i << ": ";
        for(uint32_t d = 1; d <= rt; d++)
        {
            if(i % d == 0)
            {

                if(i / d != d)
                {

                }
            }
        }
        cerr << endl;
    }
}
