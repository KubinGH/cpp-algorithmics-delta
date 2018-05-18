#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<multiset<uint32_t, greater<uint32_t>>, MAX> G;
    static array<multiset<uint32_t, greater<uint32_t>>, MAX> I;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].insert(v);
        I[v].insert(u);
    }
    deque<uint32_t> R;
    set<deque<uint32_t>> S;
    S.insert({0});
    while(not S.empty())
    {
        deque<uint32_t> C, U = *S.begin();
        S.erase(S.begin());
        uint32_t v0 = U[0];
        for(uint32_t v : U)
        {
            R.push_back(v);
            while(not I[v].empty())
            {
                uint32_t w = *I[v].begin();
                I[v].erase(I[v].begin());
                C.push_front(v);
                v = w;
                if(v == v0)
                {
                    S.insert(C);
                    C = deque<uint32_t>();
                }
            }
        }
        if(not C.empty())
            S.insert(C);
    }
    for(uint32_t u : R)
        cout << u+1 << " ";
}
