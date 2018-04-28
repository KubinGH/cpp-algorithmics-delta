#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1e4;

int main()
{
    uint32_t t;
    scanf("%u", &t);
for(uint32_t ti = 0; ti < t; ti++)
{
    uint32_t n, m;
    scanf("%u %u", &n, &m);
    bool ok = true;
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < n; i++)
        graph[i].clear();
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        scanf("%u %u", &u, &v); u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    static bool visited[MAX], color[MAX];
    vector<uint32_t> diffs;
    fill(visited, visited + n, false);
    fill(color, color + n, false);
    map<uint32_t, uint32_t> M;
    uint32_t diffsum = 0;
    for(uint32_t s = 0; s < n; s++)
    {
        if(visited[s])
            continue;
        stack<uint32_t> S;
        S.push(s); visited[s] = true; color[s] = 0;
        //cout << s << ": " << endl;
        uint32_t c0 = 0, c1 = 0;
        while(not S.empty())
        {
            uint32_t u = S.top(); S.pop();
            if(color[u] == 0) c0++;
            else c1++;
            //cout << u << " " << color[u] << endl;
            for(uint32_t i = 0; i < graph[u].size(); i++)
            {
                uint32_t v = graph[u][i];
                if(visited[v] and color[v] == color[u])
                {
                    ok = false;
                    goto after;
                }
                else if(not visited[v])
                {
                    visited[v] = true;
                    color[v] = not color[u];
                    S.push(v);
                }
            }
        }
        diffs.push_back(c0 > c1 ? c0 - c1 : c1 - c0);
        diffsum += diffs.back(), M[diffs.back()]++;
    }
    if(diffsum % 2 == 1)
    {
        ok = false;
        goto after;
    }
    static bool A[MAX+1];
    fill(A, A+diffsum/2+1, false);
    A[0] = true;
    for(map<uint32_t, uint32_t>::iterator it = M.begin();
        it != M.end(); it++)
    {
        pair<uint32_t, uint32_t> p = *it;
        for(uint32_t i = diffsum/2+1; i --> 0;)
        {
            if(A[i])
            {
                for(uint32_t x = i+p.first, k = 0;
                    k < p.second and x <= diffsum/2;
                    k++, x += p.first)
                     A[x] = true;
            }
        }
    }
    if(not A[diffsum/2])
    {
        ok = false;
        goto after;
    }
after:
    if(ok)
        cout << "TAK\n";
    else
        cout << "NIE\n";
}
}
