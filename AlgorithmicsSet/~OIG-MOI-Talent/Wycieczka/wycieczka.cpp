#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200000;

typedef unsigned int uint32_t;

pair<uint32_t, vector<pair<uint32_t, uint32_t> > >
furthest_away(const vector<pair<uint32_t, uint32_t> > (&G)[MAX],
              uint32_t start, bool make_path = true)
{
    queue<pair<uint32_t, uint32_t> > Q;
    Q.push(make_pair(start, 0));
    uint32_t result = start, result_dist = 0;
    static bool V[MAX]; fill(V, V + MAX, false);
    static pair<uint32_t, uint32_t> P[MAX];
    V[start] = true; P[start].first = start, P[start].second = 0;
    while(not Q.empty())
    {
        uint32_t u = Q.front().first, d = Q.front().second; Q.pop();
        if(d > result_dist)
            result = u, result_dist = d;
        for(uint32_t i = 0; i < G[u].size(); i++)
        {
            uint32_t v = G[u][i].first, w = G[u][i].second;
            if(not V[v])
            {
                Q.push(make_pair(v, d + w));
                V[v] = true; P[v].first = u, P[v].second = w;
            }
        }
    }
    vector<pair<uint32_t, uint32_t> > path;
    if(make_path)
    {
        path.push_back(make_pair(result, 0));
        uint32_t u = result;
        while(P[u].first != u)
            path.push_back(P[u]), u = P[u].first;
    }
    return make_pair(result, path);
}

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static vector<pair<uint32_t, uint32_t> > G[MAX];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v, w;
        scanf("%u %u %u", &u, &v, &w); u--; v--;
        G[u].push_back(make_pair(v, w));
        G[v].push_back(make_pair(u, w));
    }
    uint32_t a = furthest_away(G, 0, false).first;
    pair<uint32_t, vector<pair<uint32_t, uint32_t> > > fresult = furthest_away(G, a);
    uint32_t b = fresult.first;
    vector<pair<uint32_t, uint32_t> > T = fresult.second;
    //cerr << a+1 << " " << b+1 << endl;
    //for(pair<uint32_t, uint32_t> p : T)
    //    cerr << p.first+1 << " "; cerr << endl;
    static uint32_t P[MAX], S[MAX], I[MAX];
    static vector<pair<uint32_t, uint32_t> > C[MAX];
    static bool V[MAX];
    stack<uint32_t> Q;
    Q.push(a); P[a] = a; V[a] = true;
    while(not Q.empty())
    {
        uint32_t u = Q.top();
        //cerr << "@ " << u+1 << endl;
        for(; I[u] < G[u].size(); I[u]++)
        {
            uint32_t v = G[u][I[u]].first, w = G[u][I[u]].second;
            if(not V[v])
            {
                P[v] = u;
                V[v] = true;
                C[u].push_back(make_pair(v, w));
                Q.push(v);
                break;
            }
        }
        if(I[u] == G[u].size())
        {
            for(uint32_t i = 0; i < C[u].size(); i++)
                S[u] += S[C[u][i].first], S[u] += C[u][i].second;
            Q.pop();
            //cerr << u+1 << ": " << S[u] << endl;
        }
    }
    uint32_t result = 0;
    for(uint32_t i = 0; i < T.size(); i++)
    {
        uint32_t u = T[i].first, w = T[i].second;
        result += w;
        //cerr << "in path " << u+1 << " " << w << endl
        for(uint32_t j = 0; j < C[u].size(); j++)
        {
            uint32_t v = C[u][j].first, uw = C[u][j].second;
            if((i == T.size() - 1 or v != T[i+1].first) and (i == 0 or v != T[i-1].first))
                result += 2 * (S[v] + uw);
        }
    }
    printf("%u", result);
}
