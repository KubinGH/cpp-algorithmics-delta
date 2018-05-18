#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e4;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static pair<uint32_t, uint32_t> events[2*MAX];
    uint32_t time = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a, b;
        cin >> a >> b;
        events[2*i].first = a; events[2*i].second = i;
        events[2*i+1].first = b+1; events[2*i+1].second = i;
        time = max(b+1, time);
    }
    sort(events, events + 2*n);
    uint32_t ei = 0;
    static bitset<MAX> c_active, active[MAX];
    for(uint32_t t = 0; t <= time; t++)
    {
        while(ei < 2*n and events[ei].first <= t)
        {
            c_active[events[ei].second] = not c_active[events[ei].second];
            ei++;
        }
        active[t] = c_active;
    }
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t k;
        cin >> k;
        c_active.reset();
        for(uint32_t j = 0; j < k; j++)
        {
            uint32_t a;
            cin >> a;
            c_active |= active[a];
        }
        cout << c_active.count() << "\n";
    }
}
