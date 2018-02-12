#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<uint32_t>, MAX> graph;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    queue<uint32_t> Q;
    static array<bool, MAX> C;
    static array<uint32_t, MAX> D;
    Q.push(0);
    C[0] = true;
    while(not Q.empty())
    {
        uint32_t c = Q.front(); Q.pop();
        for(uint32_t n : graph[c])
        {
            if(not C[n])
            {
                C[n] = true;
                D[n] = D[c] + 1;
                Q.push(n);
            }
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        if(i == 0 or D[i] != 0)
            cout << D[i] << '\n';
        else
            cout << "-1\n";
    }
}
