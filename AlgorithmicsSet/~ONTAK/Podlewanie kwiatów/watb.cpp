#include <bits/stdc++.h>

using namespace std;

struct funnel { int64_t l, r, h, w; };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t m; int64_t n;
    cin >> m >> n;

    if(n == 1) { cout << 0; return 0; }

    vector<funnel> F(m);
    for(size_t i = 0; i < m; i++)
        cin >> F[i].l >> F[i].r >> F[i].h >> F[i].w;

    int64_t result = INT64_MAX;
    for(size_t v = 0; v < (1u << m); v++)
    {
        int64_t cost = 0;
        bool none = true;
        int64_t l = -1, r = -1;
        for(size_t i = m; i --> 0; ) if(v & (1 << i))
        {
            cost += F[i].w;
            if(none)
                l = F[i].l, r = F[i].r, none = false;
            else
            {
                if(l <= F[i].h and F[i].h <= r)
                {
                    l = min(l, F[i].l);
                    r = max(r, F[i].r);
                }
            }
        }
        if(l == 1 and r == n)
            result = min(result, cost);
    }

    cout << (result == INT64_MAX ? -1 : result);
}
