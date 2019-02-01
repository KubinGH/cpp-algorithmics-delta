#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<uint32_t, uint32_t>>> G;
map<uint32_t, uint32_t> T;

map<uint32_t, uint32_t> dfs_map(uint32_t u, uint32_t block = -1u, uint32_t depth = 0)
{
    map<uint32_t, uint32_t> D;
    for(auto e : G[u]) if(e.first != block)
    {
        uint32_t v = e.first, w = e.second;
        auto Ds = dfs_map(v, u, depth + 1);
        for(auto p : Ds)
            T[p.first - depth - 1] += p.second * w;
        if(D.size() < Ds.size())
            swap(D, Ds);
        for(auto p : Ds)
            D[p.first] += p.second;
    }
    if(G[u].size() == 1 and G[u][0].first == block)
        D[depth]++;
    return D;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    G.resize(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--; v--;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    vector<uint32_t> R(n+4, -1u), C(n+4);
    vector<uint32_t> B;

    for(uint32_t i = 0; i < n; i++)
    {
        T.clear();
        dfs_map(i);
        fill(C.begin(), C.end(), 0);
        for(uint32_t i = 0; i < n+4; i++)
        {
            C[i] += T[i];
            if(C[i] > 10)
                C[i+1] += C[i]/10, C[i] %= 10;
        }
        if(lexicographical_compare(C.rbegin(), C.rend(), R.rbegin(), R.rend()))
            B.clear(), R = C;
        if(C == R)
            B.push_back(i);
    }

    sort(B.begin(), B.end());
    cout << B.size() << "\n";
    for(uint32_t i : B)
        cout << i+1 << " ";
}
