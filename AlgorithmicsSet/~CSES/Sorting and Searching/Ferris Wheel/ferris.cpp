#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int x;
    cin >> n >> x;

    multiset<int> weights;
    while(n --> 0)
    {
        int w;
        cin >> w;
        weights.insert(w);
    }

    size_t result = 0;
    while(not weights.empty())
    {
        auto it1 = weights.begin();
        auto a = *it1;
        weights.erase(it1);
        auto it2 = weights.upper_bound(x - a);
        if(not weights.empty() and it2 != weights.begin())
            weights.erase(--it2);
        result++;
    }

    cout << result << endl;
}
