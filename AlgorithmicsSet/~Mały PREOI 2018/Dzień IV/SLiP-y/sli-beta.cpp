#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    unordered_map<string, uint32_t> TI;
    vector<string> TS(n);
    for(uint32_t i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        TI[s] = i; TS[i] = s;
    }
    vector<vector<uint32_t>> M(n+1, vector<uint32_t>(n+1, 1));
    for(uint32_t i = 0; i <= n; i++)
        M[i][i] = 0, M[i][n] = 0, M[n][i] = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        string a; uint32_t _; string b;
        cin >> a >> _ >> _ >> b;
        M[TI[a]][TI[b]] = 0;
        M[TI[b]][TI[a]] = 0;
    }

    vector<vector<uint32_t>> G(n+1);
    for(uint32_t u = 0; u < n; u++)
        for(uint32_t v = 0; v < n; v++)
            if(M[u][v]) G[u].push_back(v);
    uint32_t r = 0;
    for(uint32_t u = 0; u < n; u++)
    {
        if(G[u].size() % 2)
        {
            r++;
            G[u].push_back(n), G[n].push_back(u);
            M[u][n]++; M[n][u]++;
        }
    }
    if(G[n].size() % 2)
        M[n][n]++, G[n].push_back(n);

    cout << r << "\n";

    // Euler's path

    auto assert_valid_edges = [&](uint32_t u) {
        while(not G[u].empty() and M[u][G[u].back()] == 0)
            G[u].pop_back();
    };

    for(uint32_t i = 0; i < n; i++)
    {
        stack<uint32_t> S;
        S.push(i);
        while(not S.empty())
        {
            uint32_t u = S.top();
            assert_valid_edges(u);
            if(G[u].empty())
                S.pop();
            else
            {
                uint32_t v = G[u].back();
                G[u].pop_back(); M[u][v]--; if(u != v) M[v][u]--;
                if(u < n and v < n)
                    cout << TS[u] << " " << TS[v] << "\n";
                S.push(v);
            }
        }
    }
}
