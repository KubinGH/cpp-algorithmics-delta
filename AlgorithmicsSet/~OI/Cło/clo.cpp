#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000, MAX_E = 200000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<pair<uint32_t, uint32_t>>, MAX> G;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
    }
    static array<bool, MAX> DV;
    static array<bool, MAX_E> DE;
    static array<uint32_t, MAX> prev;
    unordered_set<uint32_t> todo;
    for(uint32_t i = 0; i < n; i++)
        todo.insert(i);
    vector<uint32_t> parts;
    while(not todo.empty())
    {
        uint32_t start = *todo.begin(); todo.erase(todo.begin());
        DV[start] = true;
        prev[start] = -1;
        uint32_t cv = 1, ce = 0;
        stack<uint32_t> S;
        S.push(start);
        bool found_cycle = false;
        while(not S.empty())
        {
            uint32_t u = S.top(); S.pop();
            for(pair<uint32_t, uint32_t> e : G[u])
            {
                uint32_t v = e.first, i = e.second;
                if(not DE[i])
                    ce++, DE[i] = true;
                if(not DV[v])
                {
                    cv++, DV[v] = true;
                    prev[v] = u;
                    todo.erase(v);
                    S.push(v);
                }
                else if(not found_cycle and prev[u] != v)
                {
                    found_cycle = true;
                    start = v;
                }
            }
        }
        if(cv == ce + 1)
        {
            cout << "NIE";
            return 0;
        }
        parts.push_back(start);
    }
    DV.fill(false); DE.fill(false);
    static array<uint32_t, MAX> R;
    static array<vector<uint32_t>, MAX> GT;
    static array<uint32_t, MAX> I;
    for(uint32_t start : parts)
    {
        stack<uint32_t> S;
        S.push(start);
        DV[start] = true;
        while(not S.empty())
        {
            uint32_t u = S.top();
            if(I[u] >= G[u].size())
            {
                S.pop();
            }
            for(; I[u] < G[u].size(); I[u]++)
            {
                uint32_t v = G[u][I[u]].first, i = G[u][I[u]].second;
                if(not DV[v])
                {
                    R[v] = u;
                    DV[v] = true;
                    DE[i] = true;
                    I[u]++;
                    S.push(v);
                    break;
                }
            }
        }
        for(pair<uint32_t, uint32_t> e : G[start])
        {
            if(not DE[e.second])
            {
                R[start] = e.first;
                break;
            }
        }
    }
    cout << "TAK\n";
    for(uint32_t i = 0; i < n; i++)
        cout << R[i] + 1 << '\n';
}
