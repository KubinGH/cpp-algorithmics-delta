#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    multiset<int> slots;
    while(n --> 0)
    {
        int a;
        cin >> a;

        auto it = slots.upper_bound(a);
        if(it != slots.end())
            slots.erase(it);
        slots.insert(a);
    }

    cout << slots.size() << endl;
}
