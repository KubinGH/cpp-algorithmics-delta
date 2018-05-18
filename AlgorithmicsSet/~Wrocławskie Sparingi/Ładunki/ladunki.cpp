#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 32;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static bitset<MAX> conn[MAX];
    vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        if(not conn[u][v])
        {
            conn[u][v] = conn[v][u] = true;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }
    static bool vis[MAX]; fill(vis, vis + MAX, false);
    static char final_result[MAX];
    for(uint32_t src = 0; src < n; src++)
    {
        if(vis[src])
            continue;
        // Find connected component
        vector<uint32_t> comp;
        static uint32_t comp_i[MAX];
        stack<uint32_t> to_vis;
        vis[src] = true; to_vis.push(src);
        comp.push_back(src);
        while(not to_vis.empty())
        {
            uint32_t u = to_vis.top(); to_vis.pop();
            for(uint32_t v : graph[u])
            {
                if(not vis[v])
                {
                    vis[v] = true;
                    to_vis.push(v);
                    comp.push_back(v);
                }
            }
        }
        sort(comp.begin(), comp.end());
        for(uint32_t i = 0; i < comp.size(); i++)
            comp_i[comp[i]] = i;
        static char M_curr_result[MAX], M_conn_result[MAX];
        char *curr_result = M_curr_result, *conn_result = M_conn_result;
        bool has_any = false;
        for(uint32_t mask = 0; mask < (1u << comp.size()); mask++)
        {
            for(uint32_t i = 0; i < comp.size(); i++)
            {
                if(mask & (1u << i))
                    curr_result[i] = 'A';
                else
                    curr_result[i] = 0;
            }
            for(uint32_t i = 0; i < comp.size(); i++)
            {
                if(curr_result[i] == 'A')
                    for(uint32_t v : graph[comp[i]])
                        if(curr_result[i] == curr_result[comp_i[v]])
                            goto fail;
            }
            for(uint32_t s = 0; s < comp.size(); s++)
            {
                if(curr_result[s] != 0)
                    continue;
                stack<uint32_t> to_vis;
                to_vis.push(s);
                curr_result[s] = 'B';
                while(not to_vis.empty())
                {
                    uint32_t u = to_vis.top(); to_vis.pop();
                    for(uint32_t v : graph[comp[u]])
                    {
                        v = comp_i[v];
                        if(curr_result[v] == curr_result[u])
                            goto fail;
                        else if(curr_result[v] == 0)
                        {
                            curr_result[v] = (curr_result[u] == 'B') ? 'C' : 'B';
                            to_vis.push(v);
                        }
                    }
                }
            }
            if(not has_any)
            {
                swap(curr_result, conn_result);
                has_any = true;
            }
            else
            {
                if(lexicographical_compare(
                    curr_result, curr_result + comp.size(),
                    conn_result, conn_result + comp.size()))
                {
                    swap(curr_result, conn_result);
                }
            }
        fail:;
        }
        if(not has_any)
            goto total_fail;
        for(uint32_t i = 0; i < comp.size(); i++)
            final_result[comp[i]] = conn_result[i];
    }
    for(uint32_t i = 0; i < n; i++)
        cout << final_result[i];
    return 0;
total_fail:
    cout << "NIE";
}
