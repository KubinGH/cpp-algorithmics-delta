#include <bits/stdc++.h>
#define BIT_SET(n, i)   (n |= (1u << i))
#define BIT_UNSET(n, i) (n &= ~(1u << i))

using namespace std;

const size_t MAX = 25;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static vector<uint32_t> G[MAX];
    static uint32_t Q[MAX];
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
        BIT_SET(Q[u], v);
        BIT_SET(Q[v], u);
    }
    static uint32_t O[MAX], M[MAX];
    fill(O, O+n, -1u);
    static vector<uint32_t> U[MAX];
    static bool LS[MAX];
    fill(LS, LS + n, false);
    for(uint32_t p = 0; p < m; p++)
    {
        if(O[p] != -1u)
            continue;
        stack<uint32_t> S;
        S.push(p); O[p] = p; U[p].push_back(p), M[p] = p;
        while(not S.empty())
        {
            uint32_t u = S.top(); S.pop();
            for(uint32_t v : G[u])
            {
                if(O[v] == -1u)
                {
                    S.push(v);
                    O[v] = p; U[p].push_back(v);
                    M[p] = max(M[p], v);
                }
            }
        }
    }
    static char R[MAX];
    static char MC[MAX], ML[MAX];
    char* C = MC, *L = ML;
    for(uint32_t s = 0; s < (1u << n); s++)
    {
        uint32_t a = 0;
        for(uint32_t i = 0; i < n; i++)
            if(s & (1u << i))
                C[i] = 'A', BIT_SET(a, i);
            else
                C[i] = 0;
        bool ok = true;
        for(uint32_t u = 0; u < n; u++)
        {
            if(C[u] != 0)
            {
                if((a & Q[u]) != 0)
                {
                    ok = false;
                    break;
                }
            }
        }
        if(not ok)
            continue;
        for(uint32_t p = 0; p < n; p++)
        {
            if(C[p] != 0)
                continue;
            bool flag = false;
            for(uint32_t u : U[O[p]])
            {
                if(s == 0 or ((s-1) & (1u << u)) != (s & (1u << u)))
                {
                    flag = true;
                    break;
                }
            }
            if(not flag)
            {
                if(LS[O[p]])
                {
                    for(uint32_t u : U[O[p]])
                        C[u] = L[u];
                    continue;
                }
                else
                {
                    ok = false;
                    break;
                }
            }
            static uint32_t S[MAX]; uint32_t si = 0;
            S[si++] = p;
            C[p] = 'B';
            while(si)
            {
                uint32_t u = S[si-1]; si--;
                for(uint32_t v : G[u])
                {
                    if(C[v] == C[u])
                    {
                        ok = false;
                        break;
                    }
                    else if(C[v] == 0)
                    {
                        if(C[u] == 'C')
                            C[v] = 'B';
                        else if(C[u] == 'B')
                            C[v] = 'C';
                        S[si++] = v;
                    }
                }
            }
            if(not ok)
            {
                LS[O[p]] = false;
                break;
            }
            else if(p == M[O[p]])
            {
                LS[O[p]] = true;
                for(uint32_t u : U[O[p]])
                    L[u] = C[u];
            }
        }
        if(not ok)
            continue;
        else
        {
            if(R[0]==0 or lexicographical_compare(C, C+n, R, R+n))
                copy(C, C+n, R);
            for(uint32_t i = 0; i < n; i++)
                if(C[i] == 'B') C[i] = 'C';
                else if(C[i] == 'C') C[i] = 'B';
            if(lexicographical_compare(C, C+n, R, R+n))
                copy(C, C+n, R);
        }
    }
    if(R[0] != 0)
    {
        for(uint32_t i = 0; i < n; i++)
            cout << R[i];
    }
    else
        cout << "NIE";
}
