#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<tuple<int, bool, size_t>> events;
    for(size_t i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        events.emplace_back(a, 0, i);
        events.emplace_back(b, 1, i);
    }

    size_t k = 0;
    set<size_t> free;
    vector<size_t> room(n);
    sort(events.begin(), events.end());

    for(auto [_, t, i] : events)
    {
        if(t == 0)
        {
            if(free.empty())
                free.insert(++k);
            room[i] = *free.begin();
            free.erase(free.begin());
        }
        else
            free.insert(room[i]);
    }

    cout << k << endl;
    for(auto r : room)
        cout << r << ' ';
    cout << endl;
}
