#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;

typedef pair<uint64_t, uint32_t> dij_dt;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static uint64_t P[MAX][2];
    static uint32_t L[MAX][2];
    static pair<uint32_t, bool> LV[MAX][2];
    static vector<uint32_t> G[MAX];
    map<pair<uint32_t, uint32_t>, uint32_t> D;
    static pair<uint32_t, uint32_t> E[MAX];
    static uint64_t W[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v >> W[i]; u--; v--;
        G[u].emplace_back(i);
        G[v].emplace_back(i);
        E[i] = {u, v};
    }
    priority_queue<dij_dt, vector<dij_dt>, greater<dij_dt>> Q;
    fill(&P[0][0], &P[n][1] + 1, -1llu);
    fill(&L[0][0], &L[n][1] + 1, -1u);
    fill(&LV[0][0], &LV[n][1] + 1, pair<uint32_t, bool>{-1u, 0});
    P[0][0] = 0;
    Q.emplace(0, 0);
    while(not Q.empty())
    {
        auto p = Q.top(); Q.pop();
        uint32_t u = p.second; uint64_t c = p.first;
        cerr << u+1 << " @ " << c << endl;
        for(auto e : G[u])
        {
            uint32_t v = E[e].first==u ? E[e].second : E[e].first;
            uint64_t w = W[e];
            if(P[u][0] + w < P[v][0])
            {
                P[v][0] = c + w;
                L[v][0] = e;
                LV[v][0] = {u, 0};
                Q.emplace(P[v][0], v);
            }
            if(P[u][0] + w > P[v][0] and P[u][0] + w < P[v][1])
            {
                P[v][1] = P[u][0] + w;
                L[v][1] = e;
                LV[v][1] = {u, 0};
                Q.emplace(P[v][0], v);
            }
            if(P[u][1] != -1llu and P[u][1] + w > P[v][0] and P[u][1] + w < P[v][1])
            {
                P[v][1] = P[u][1] + w;
                L[v][1] = e;
                LV[v][1] = {u, 1};
                Q.emplace(P[v][1], v);
            }
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        cerr << i+1 << ": " << P[i][0] << " /" << P[i][1] << " (#"
             << L[i][0]+1 << " /" << L[i][1]+1 << ")" << endl;
    }
    uint32_t c = n-1; bool o = 1;
    vector<uint32_t> UE;
    while(c)
    {
        UE.push_back(L[c][o]);
        tie(c, o) = LV[c][o];
    }
    sort(UE.begin(), UE.end());
    cout << UE.size() << "\n";
    for(uint32_t e : UE)
        cout << e+1 << " ";
}
