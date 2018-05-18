#include <bits/stdc++.h>

using namespace std;

int main()
{
    int64_t n, p, q, k;
    cin >> n >> p >> q >> k;
    priority_queue<pair<int64_t, int64_t>> Q;
    for(int64_t i = 0; i < n; i++)
    {
        int64_t m, c;
        cin >> m >> c;
        Q.emplace(c, m);

        if(p >= c)
        {
            p -= c;
            q += m;
        }
        q -= k;
        if(q < 0ll)
        {
            cout << i;
            return 0;
        }
    }
    cout << "MILIONER";
}
