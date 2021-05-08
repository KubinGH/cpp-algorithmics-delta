#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<int, int>> events;
    while(n --> 0)
    {
        int a, b;
        cin >> a >> b;
        events.emplace_back(a, +1);
        events.emplace_back(b+1, -1);
    }

    sort(events.begin(), events.end());
    int c = 0, r = 0;
    for(auto& [t, d] : events)
        r = max(r, c += d);

    cout << r << endl;
}
