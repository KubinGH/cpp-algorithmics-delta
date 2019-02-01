#include <bits/stdc++.h>
#define REPR(n) (-1 ? (n == INF) : static_cast<int64_t>(n))

using namespace std;

const size_t MAX = 100;
const uint64_t INF = numeric_limits<uint64_t>::max();
const uint32_t INF32 = numeric_limits<uint32_t>::max();

array<bool, MAX> visited;
array<uint32_t, MAX> stack_pos, eidx;
vector<uint32_t> vstack;
uint32_t s;
static array<vector<uint64_t>, MAX> G;
array<vector<uint32_t>, MAX> cycles;

void dfs(uint32_t v)
{
    vstack.push_back(v);
    for(; eidx[v] < G[v].size(); eidx[v]++)
    {
        uint32_t u = G[v][eidx[v]];
        if(stack_pos[u] != INF32)
        {
            //cerr << "cycle @ " << u+1 << ": ";
            //for(uint32_t i : vstack)
            //    cerr << i+1 << " "; cerr << endl;
            for(uint32_t i = 0; i < s - stack_pos[u]; i++)
                cycles[vstack[s-i]].push_back(s - stack_pos[u]);
            continue;
        }
        else if(not visited[u])
        {
            visited[u] = true;
            stack_pos[u] = s++;
            dfs(u);
        }
    }
    stack_pos[v] = INF32; s--;
    vstack.pop_back();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //cerr.setstate(ios_base::failbit);
    uint32_t n, m, q;
    cin >> n >> m >> q;
    static array<array<uint64_t, MAX>, MAX> D;
    for(uint32_t i = 0; i < MAX; i++)
        D[i].fill(INF);
    for(uint32_t i = 0; i < n; i++)
        D[i][i] = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        G[a].push_back(b);
        if(D[a][b] > 0) D[a][b] = 1;
    }
    for(uint32_t k = 0; k < n; k++)
        for(uint32_t i = 0; i < n; i++)
            for(uint32_t j = 0; j < n; j++)
                if(D[i][k] != INF and D[k][j] != INF)
                    D[i][j] = min(D[i][k] + D[k][j], D[i][j]);
    /*cerr << "Distances: ";
    for(uint32_t i = 0; i < n; i++)
    {
        cerr << i+1 << ": ";
        for(uint32_t j = 0; j < n; j++)
            cerr << D[i][j] << " "; cerr << endl;
    }*/
    visited[0] = true; stack_pos.fill(INF32); stack_pos[0] = 0;
    dfs(0);
    /*cerr << "Cycles: ";
    for(uint32_t i = 0; i < n; i++)
    {
        cerr << i+1 << ": ";
        for(uint32_t c : cycles[i])
            cerr << c << " "; cerr << endl;
    }*/
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t v; uint64_t l;
        cin >> v >> l; v--;
        if(D[0][v] > l)
        {
            cout << "NIE" << '\n'; continue;
        }
        else if(D[0][v] == l)
        {
            cout << D[0][v] << '\n'; continue;
        }
        queue<tuple<uint32_t, uint64_t, bitset<MAX+1>, bitset<MAX> > > Q;
        Q.emplace(0, 0, bitset<MAX+1>(), bitset<MAX>());
        for(uint32_t x : cycles[0])
            get<2>(Q.front())[x] = true;
        get<3>(Q.front())[0] = true;
        uint64_t best = 0;
        while(not Q.empty())
        {
            auto current = Q.front(); Q.pop();
            uint32_t c = get<0>(current);
            uint64_t d = get<1>(current);
            bitset<MAX+1>& b = get<2>(current);
            bitset<MAX>& vis = get<3>(current);
            //cerr << "@ " << c+1 << " " << vis << endl;
            for(uint32_t u : G[c])
            {
                //cerr << " -> " << u+1 << endl;
                if(u == v)
                {
                    //cerr << "goal " << c+1 << " " << d << " " << b << endl;
                    uint64_t w = l - d - 1;
                    for(uint64_t i = 1; i < MAX+1; i++)
                        if(b[i])
                            w %= i;
                    uint64_t r = l - w;
                    best = max(best, r);
                }
                else if(not vis[u])
                {
                    tuple<uint32_t, uint64_t, bitset<MAX+1>, bitset<MAX> > np;
                    get<0>(np) = u;
                    get<1>(np) = d + 1;
                    get<2>(np) = b;
                    get<3>(np) = vis;
                    for(uint32_t x : cycles[u])
                        get<2>(np)[x] = true;
                    get<3>(np)[u] = true;
                    Q.emplace(np);
                }
            }
        }
        cout << best << '\n';
    }
}
