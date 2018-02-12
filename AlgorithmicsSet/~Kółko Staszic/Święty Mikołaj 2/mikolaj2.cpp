#include <bits/stdc++.h>
#define FATAL "Beeeeeeeeeeeeeee"

using namespace std;

const size_t MAX = 700000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, start;
    cin >> n >> start; start--;
    static array<vector<uint32_t>, MAX> graph;
    static array<bool, MAX> wanted;
    static array<bool, MAX> checked;
    queue<pair<uint32_t, uint32_t> > to_check;
    uint32_t result;
    bool found = false;
    for(uint32_t p = 0; p < n; p++)
    {
        uint32_t l;
        cin >> l;
        for(uint32_t i = 0; i < l; i++)
        {
            uint32_t c;
            cin >> c; c--;
            graph[c].push_back(p);
            if(p == start)
            {
                wanted[c] = true;
                if(c == start)
                {
                    result = 0;
                    found = true;
                    goto after;
                }
            }
        }
    }
    checked[start] = true;
    to_check.emplace(start, 0);
    while(not to_check.empty())
    {
        pair<uint32_t, uint32_t> cpair = to_check.front(); to_check.pop();
        uint32_t cnode = cpair.first, cdist = cpair.second;
        for(uint32_t node : graph[cnode])
        {
            if(wanted[node])
            {
                result = cdist + 1;
                found = true;
                goto after;
            }
            else if(not checked[node])
            {
                checked[node] = true;
                to_check.emplace(node, cdist + 1);
            }
        }
    }
after:
    if(found)
        cout << result;
    else
        cout << FATAL;
}
