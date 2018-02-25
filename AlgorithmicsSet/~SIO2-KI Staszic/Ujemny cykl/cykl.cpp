#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 5000, MAX_E = 10000;

stack<uint32_t> S;
array<bool, MAX> V;
static array<vector<pair_u32>, MAX> G;

bool dfs(uint32_t u, uint32_t target)
{
    //cout << "dfs(" << u+1 << ", " << target+1 << ")" << endl;
    if(u == target)
        return true;
    for(pair_u32 e : G[u])
    {
        uint32_t v = e.first, i = e.second;
        if(not V[v])
        {
            V[v] = true;
            S.push(i);
            //cout << u+1 << " -> " << v+1 << endl;
            if(dfs(v, target))
                return true;
            else
                S.pop();
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<pair_u32, MAX_E> E;
    queue<uint32_t> Q;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; int32_t c;
        cin >> u >> v >> c; u--; v--;
        G[u].emplace_back(v, i);
        if(c < 0)
            Q.push(i);
        E[i].first = u, E[i].second = v;
    }
    while(not Q.empty())
    {
        uint32_t u = E[Q.front()].first, v = E[Q.front()].second;
        V.fill(false);
        while(not S.empty()) S.pop();
        V[v] = true;
        if(dfs(v, u))
        {
            cout << "TAK" << '\n';
            cout << S.size() + 1 << " ";
            stack<uint32_t> temp;
            while(not S.empty())
                temp.push(S.top()), S.pop();
            cout << Q.front()+1 << " ";
            while(not temp.empty())
                cout << temp.top()+1 << " ", temp.pop();
            //cout << endl;
            return 0;
        }
        Q.pop();
    }
    cout << "NIE";
}
