#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, k;
    cin >> n >> k;

    vector<tuple<size_t, size_t, int>> edges(n - 1);
    for(size_t i = 0; i < n - 1; i++)
        cin >> get<0>(edges[i]) >> get<1>(edges[i]) >> get<2>(edges[i]);

    int result = INT_MIN;

    for(size_t m = 0; m < (1u << (n - 1)); m++) if(__builtin_popcount(m) == k)
    {
        bitset<64> vi;
        int sum = 0;
        bool ok = true;
        for(size_t i = 0; i < n - 1; i++)
            if(m >> i & 1)
        {
            sum += get<2>(edges[i]);
            if(vi[get<0>(edges[i])] or vi[get<1>(edges[i])])
                ok = false;
            vi[get<0>(edges[i])] = vi[get<1>(edges[i])] = true;
        }

        if(ok)
            result = max(result, sum);
    }

    if(result != INT_MIN)
        cout << "TAK\n" << result << "\n";
    else
        cout << "NIE\n";
}
