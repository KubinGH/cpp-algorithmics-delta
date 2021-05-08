#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int x; size_t n;
    cin >> x >> n;

    multiset<int> gaps = {x};
    set<int> stops = {0, x};

    while(n --> 0)
    {
        int a;
        cin >> a;

        auto it = stops.lower_bound(a);
        gaps.erase(gaps.find(*it - *prev(it)));
        gaps.insert(*it - a);
        gaps.insert(a - *prev(it));
        stops.insert(a);

        cout << *prev(gaps.end()) << '\n';
    }
}
