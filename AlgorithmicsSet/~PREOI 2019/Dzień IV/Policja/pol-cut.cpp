#include <bits/stdc++.h>

using namespace std;

void dfs_order(const vector<vector<uint32_t>>& children, uint32_t v,
               vector<uint32_t>& order, vector<uint32_t>& preorder, uint32_t& p)
{
    order.push_back(preorder[v] = p++);
    for(uint32_t u : children[v])
    {
        dfs_order(children, u, order, preorder, p);
        order.push_back(preorder[v]);
    }
}

vector<uint32_t> get_prefmexes(const vector<uint32_t>& A)
{
    vector<uint32_t> prefmex(A.size()+1);
    set<uint32_t> S;
    for(uint32_t i = 0; i < A.size(); i++)
    {
        prefmex[i+1] = prefmex[i];
        if(A[i] >= prefmex[i+1]) S.insert(A[i]);
        while(not S.empty() and *S.begin() == prefmex[i+1])
            S.erase(S.begin()), prefmex[i+1]++;
    }
    return prefmex;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;

    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<vector<uint32_t>> children(n);
    vector<uint32_t> parent(n), T; T.reserve(n);
    vector<bool> vis(n);
    queue<uint32_t> Q;
    vis[0] = true; Q.push(0);
    parent[0] = -1u;
    while(not Q.empty())
    {
        uint32_t v = Q.front(); Q.pop();
        T.push_back(v);
        for(uint32_t u : graph[v])
        {
            if(not vis[u])
            {
                vis[u] = true; Q.push(u);
                parent[u] = v;
                children[v].push_back(u);
            }
        }
    }
    reverse(T.begin(), T.end());

    if(k == 1)
    {
        vector<uint32_t> Z; Z.reserve(2*n);
        vector<uint32_t> P(n);
        uint32_t preorder = 0;
        dfs_order(children, 0, Z, P, preorder);
        const uint32_t z = Z.size();

        vector<uint32_t> prefmex = get_prefmexes(Z);
        vector<uint32_t> Zt = Z;
        reverse(Zt.begin(), Zt.end());
        for(uint32_t i = 0; i < Zt.size(); i++)
            Zt[i] = (preorder - 1) - Zt[i];
        vector<uint32_t> sufmex = get_prefmexes(Zt);
        for(uint32_t i = 0; i < sufmex.size(); i++)
            sufmex[i] = preorder - sufmex[i];
        reverse(sufmex.begin(), sufmex.end());
        for(uint32_t i = 0; i < z; i++)
            cout << Z[i] << " "; cout << endl;
        /*for(uint32_t i = 1; i <= z; i++)
            cout << prefmex[i] << " "; cout << endl;
        for(uint32_t i = 0; i < z; i++)
            cout << sufmex[i] << " "; cout << endl;*/

        uint32_t r = 0;
        for(uint32_t i = 0; i <= n; i++)
        {
            uint32_t j = lower_bound(sufmex.begin(), sufmex.end(), prefmex[i]) - sufmex.begin();
            cout << "< " << i << " " << j << " > " << endl;
            r = max(r, j - i);
        }
        cout << z - r + 1;
    }
    else
        abort();
}
