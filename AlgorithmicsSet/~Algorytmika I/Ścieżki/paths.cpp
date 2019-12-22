#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    while(q --> 0)
    {
        size_t s, t;
        cin >> s >> t; s--; t--;

        queue<size_t> Q;
        Q.push(s);
        vector<size_t> back(n, SIZE_MAX);
        back[s] = s;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto v : graph[u])
                if(back[v] == SIZE_MAX)
                    back[v] = u, Q.push(v);
        }
        if(back[t] == SIZE_MAX)
        {
            cout << "-1\n";
            continue;
        }
        vector<size_t> out = {t};
        while(t != s)
            out.push_back(t = back[t]);

        reverse(out.begin(), out.end());
        cout << out.size() - 1 << ' ';
        for(auto u : out)
            cout << u+1 << ' ';
        cout << '\n';
    }
}
