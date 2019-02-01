#include <bits/stdc++.h>

using namespace std;

using hash_t = pair<uint64_t, uint64_t>;
hash_t hashh(const string& S)
{
    hash_t r = {0, 0};
    for(char c : S)
    {
        r.first *= 331; r.second *= 331;
        r.first += int(c) - CHAR_MIN;
        r.second += int(c) - CHAR_MIN;
        r.first = (r.first >> 31) + (r.first & ((1U<<31)-1));
        r.first = (r.first >> 31) + (r.first & ((1U<<31)-1));
        if(r.first==((1U<<31)-1))
            r.first = 0;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;

    map<hash_t, set<hash_t>> G;
    set<hash_t> S, Z;

    for(uint32_t i = 0; i < n; i++)
    {
        cin.ignore();
        string T[2];
        getline(cin, T[0]); getline(cin, T[1]);
        hash_t H[2] = {hashh(T[0]), hashh(T[1])};
        G[H[0]].insert(H[1]);
        G[H[1]].insert(H[0]);
        S.insert(H[0]); Z.insert(H[1]);
    }

    bool ok = false;
    set<hash_t> V;
    for(auto s : S) if(V.find(s) == V.end())
    {
        queue<hash_t> Q;
        Q.push(s); V.insert(s);
        uint32_t m = 0;
        while(not Q.empty())
        {
            hash_t u = Q.front(); Q.pop();
            m++;
            for(hash_t v : G[u])
            {
                if(V.find(v) == V.end())
                {
                    Q.push(v);
                    V.insert(v);
                }
            }
        }
        if(m < S.size() + Z.size())
        {
            ok = true;
            break;
        }
    }

    cout << (ok ? "TAK" : "NIE");
}
