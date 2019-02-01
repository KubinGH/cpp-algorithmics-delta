#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 18;

struct edge { uint32_t v, g; bool s; };

uint32_t n, k;
vector<edge> G[N];
uint32_t A[N], F[N], fulfill = 0;
uint32_t result = -1u;

void dfs_init(uint32_t u, uint32_t block = -1u)
{
    for(auto e : G[u])
    {
        if(e.v != block)
        {
            if(e.s) F[e.g]++;
            dfs_init(e.v, u);
        }
    }
}

void dfs(uint32_t u, uint32_t block = -1u)
{
    for(auto e : G[u])
    {
        if(e.v != block)
        {
            if(not e.s)
            {
                if(F[e.g] == 0)
                    fulfill--;
                F[e.g]++;
                if(F[e.g] == A[e.g])
                    fulfill++;
            }
            else
            {
                if(F[e.g] == A[e.g])
                    fulfill--;
                F[e.g]--;
                if(F[e.g] == 0)
                    fulfill++;
            }

            dfs(e.v, u);

            if(not e.s)
            {
                if(F[e.g] == A[e.g])
                    fulfill--;
                F[e.g]--;
                if(F[e.g] == 0)
                    fulfill++;
            }
            else
            {
                if(F[e.g] == 0)
                    fulfill--;
                F[e.g]++;
                if(F[e.g] == A[e.g])
                    fulfill++;
            }
        }
    }
    if(fulfill == k)
        result = min(result, u);
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v, g;
        cin >> u >> v >> g; u--; v--; g--;
        G[u].push_back({v, g, 0});
        G[v].push_back({u, g, 1});
        A[g]++;
    }
    dfs_init(0);
    for(uint32_t g = 0; g < k; g++)
        if(F[g] == 0 or F[g] == A[g])
            fulfill++;
    dfs(0);
    cout << result+1;
}
