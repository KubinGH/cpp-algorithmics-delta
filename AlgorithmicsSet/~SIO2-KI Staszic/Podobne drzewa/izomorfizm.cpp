#include <bits/stdc++.h>

using namespace std;

struct edge_t { uint32_t u, v; };
struct graph_t
{
    uint32_t V; vector<edge_t> E;
    vector<vector<uint32_t>> N;
    graph_t(uint32_t _V) : V(_V), N(V) {}
    void read_edges(uint32_t e, uint32_t fix)
    {
        while(e --> 0)
        {
            uint32_t a, b; cin >> a >> b; a += fix; b += fix;
            E.push_back({a, b});
            N[a].push_back(b);
            N[b].push_back(a);
        }
    }
};

vector<uint32_t> centers(const graph_t& G)
{
    vector<uint32_t> D(G.V);
    for(auto e : G.E)
        D[e.u]++, D[e.v]++;
    vector<uint32_t> P, Q;
    for(uint32_t u = 0; u < G.V; u++)
        if(D[u] == 1)
            Q.push_back(u);
    uint32_t V = G.V;
    while(V > 2)
    {
        for(uint32_t u : Q)
          for(uint32_t v : G.N[u])
        {
            D[u]--;
            if(--D[v] == 1)
                P.push_back(v);
        }
        V -= Q.size();
        swap(P, Q); P.clear();
    }
    return Q;
}

uint32_t hash_root(const graph_t& G, uint32_t u, uint32_t block,
                   map<vector<uint32_t>, uint32_t>& dict, uint32_t& chash)
{
    vector<uint32_t> H;
    for(uint32_t v : G.N[u])
        if(v != block)
            H.push_back(hash_root(G, v, u, dict, chash));
    if(H.empty())
        return 0;
    sort(H.begin(), H.end());
    auto it = dict.find(H);
    if(it != dict.end())
        return it->second;
    else
        return dict[H] = chash++;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    graph_t S(n), Z(n);
    S.read_edges(n-1, -1); Z.read_edges(n-1, -1);
    map<vector<uint32_t>, uint32_t> dict; uint32_t chash = 1;
    auto thash = [&](const graph_t& G, uint32_t u) {
        return hash_root(G, u, -1u, dict, chash);
    };
    cout << (thash(S, 0) == thash(Z, 0) ? "TAK" : "NIE");
    /*
    // Unrooted version
    vector<uint32_t> Sc = centers(S), Zc = centers(Z);
    if(Sc.size() != Zc.size())
        cout << "NIE";
    else
    {
        if(Sc.size() == 1)
            cout << (thash(S, Sc[0]) == thash(Z, Zc[0])
                     ? "TAK" : "NIE");
        else
            cout << (thash(S, Sc[0]) == thash(Z, Zc[0]) or thash(S, Sc[1]) == thash(Z, Zc[0])
                     ? "TAK" : "NIE");
    }
    */
}
