#include <bits/stdc++.h>

using namespace std;

const uint32_t MAX_RESULT = 300;

int main()
{
    uint32_t n, m, k;
    cin >> n >> m >> k;
    vector<vector<uint32_t>> graph(n), possible(k);
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t u;
        cin >> u; u--;
        possible[i].push_back(u);
    }
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }
    bool done = false;
    for(uint32_t r = 0; r <= MAX_RESULT; r++)
    {
        vector<uint32_t> uni(n), nuni;
        iota(uni.begin(), uni.end(), 0);
        for(const auto& p : possible)
        {
            set_intersection(uni.begin(), uni.end(), p.begin(), p.end(), back_inserter(nuni));
            uni.swap(nuni);
            nuni.clear();
        }
        if(not uni.empty())
        {
            cout << "TAK" << endl << r << endl;
            done = true;
            break;
        }

        for(uint32_t i = 0; i < k; i++)
        {
            vector<uint32_t> nxt;
            for(uint32_t u : possible[i])
                for(uint32_t v : graph[u])
                    nxt.push_back(v);
            sort(nxt.begin(), nxt.end());
            nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
            possible[i].swap(nxt);
        }
    }
    if(not done)
        cout << "NIE" << endl;

}