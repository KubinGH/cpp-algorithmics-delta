#include <bits/stdc++.h>

using namespace std;

const size_t N = 303, C = 26;

template<typename T>
struct priority_queue_01
{
    queue<T> S[2];
    priority_queue_01() {}
    void push(T e, bool w) { S[w].push(e); }
    void pop() { (S[0].empty() ? S[1] : S[0]).pop(); }
    const T& top() const { return (S[0].empty() ? S[1] : S[0]).front(); }
    bool empty() const { return S[0].empty() and S[1].empty(); }
    size_t size() const { return S[0].size() + S[1].size(); }
};

struct state
{
    uint16_t u, save, pref, need;
    state(int _u, int _save, int _pref, int _need)
        : u(_u), save(_save), pref(_pref), need(_need) {}
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<pair<uint32_t, char>> G[N];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; char c;
        cin >> u >> v >> c; u--; v--;
        G[u].emplace_back(v, c);
    }
    uint32_t X, Y;
    cin >> X >> Y; X--; Y--;
    string S; cin >> S; uint32_t nS = S.size();
    reverse(S.begin(), S.end());

    #define I(__u, __k, __p) ((__p) + (nS+1)*(__k) + (n*n)*(nS+1)*(__u))
    vector<uint16_t> T(n*n*n*(nS+1));
    vector<bool> V(n*n*n*(nS+1));

    priority_queue_01<state> Q;
    Q.push({(int)X, 0, 0, 0}, 0);
    #define VIS(__u, __k, __p, __n, __w) \
        { V[I((__u), (__k), (__p))] = true; Q.push({int(__u), int(__k), int(__p), int(__n)}, (__w)); }
    uint16_t result = numeric_limits<uint16_t>::max();
    while(not Q.empty())
    {
        auto s = Q.top(); Q.pop();
        //cerr << s.u+1 << ", " << s.save << " /$ " << s.pref << " @ " << s.need << endl;
        if(s.pref == nS and s.save == 0 and s.u == Y)
        {
            result = s.need;
            break;
        }
        for(auto e : G[s.u])
        {
            uint32_t v; char c;
            tie(v, c) = e;
            if(c == '!')
            {
                if(s.save)
                {
                    if(not V[I(v, s.save-1, s.pref)])
                        VIS(v, s.save-1, s.pref, s.need, 0);
                }
                else if(s.pref)
                {
                    if(not V[I(v, s.save, s.pref-1)])
                        VIS(v, s.save, s.pref-1, s.need, 0);
                }
            }
            else if(c == '.')
            {
                if(not V[I(v, s.save, s.pref)])
                    VIS(v, s.save, s.pref, s.need, 0);
            }
            else if('a' <= c and c <= 'z')
            {
                bool b = (s.save + s.pref + 1 > s.need);
                if(not s.save and s.pref < nS and S[s.pref] == c)
                {
                    if(not V[I(v, s.save, s.pref+1)])
                        VIS(v, s.save, s.pref+1, s.need+b, b);
                }
                else if(s.save+1 < int(n*n))
                {
                    if(not V[I(v, s.save+1, s.pref)])
                        VIS(v, s.save+1, s.pref, s.need+b, b);
                }
            }
        }
    }
    if(result == numeric_limits<uint16_t>::max())
        cout << "NIE";
    else
        cout << result;
}
