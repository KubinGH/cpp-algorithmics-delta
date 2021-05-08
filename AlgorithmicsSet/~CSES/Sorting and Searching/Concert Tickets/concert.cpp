#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    multiset<int, greater<int>> tickets;
    while(n --> 0)
    {
        int x;
        cin >> x;
        tickets.insert(x);
    }

    while(m --> 0)
    {
        int y;
        cin >> y;
        auto it = tickets.lower_bound(y);
        cout << (it == tickets.end() ? -1 : *it) << '\n';
        if(it != tickets.end())
            tickets.erase(it);
    }
}
