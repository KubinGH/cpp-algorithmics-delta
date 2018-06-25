#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5e5;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static vector<uint32_t> children[MAX];
    for(uint32_t u = 1; u < n; u++)
    {
        uint32_t p;
        cin >> p; p--;
        children[p].push_back(u);
    }
    static uint32_t subcount[MAX];
    static double subresult[MAX];
    double result = 0;
    for(uint32_t u = n; u --> 0; )
    {
        subcount[u] = 1;
        for(uint32_t v : children[u])
            subcount[u] += subcount[v];
        if(subcount[u] > 1) for(uint32_t v : children[u])
        {
            subresult[u] = max(subresult[u],
                               min(subresult[v],
                                   double(subcount[v])
                                    / double(subcount[u] - 1)));
        }
        else
            subresult[u] = 1;
        if(subcount[u] > k)
            result = max(result, subresult[u]);
    }
    cout << fixed << setprecision(10);
    cout << result;
}
