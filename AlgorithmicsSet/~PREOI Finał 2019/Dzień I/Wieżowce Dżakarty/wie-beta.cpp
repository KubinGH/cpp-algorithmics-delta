#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;

    uint32_t source = -1u, target = -1u;

    vector<unordered_set<uint32_t>> loc(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t b, p;
        cin >> b >> p;
        if(i == 0)
            source = b;
        else if(i == 1)
            target = b;
        loc[b].insert(p);
    }

    vector<forward_list<uint32_t>> queues(16*n);
    queues[0].push_front(source);

    for(uint32_t d = 0; d < queues.size(); d++) while(not queues[d].empty())
    {
        uint32_t b = queues[d].front(); queues[d].pop_front();
        if(b == target)
        {
            cout << d;
            return 0;
        }
        for(uint32_t p : loc[b])
        {
            for(uint32_t x = 1; b+p*x < n; x++)
            {
                loc[b+p*x].erase(p);
                while(queues.size() <= d+x) queues.emplace_back();
                queues[d+x].push_front(b+p*x);
            }
            for(uint32_t x = 1; b-p*x < n; x++)
            {
                loc[b-p*x].erase(p);
                while(queues.size() <= d+x) queues.emplace_back();
                queues[d+x].push_front(b-p*x);
            }
        }
        loc[b].clear();
    }
    cout << -1;
}
