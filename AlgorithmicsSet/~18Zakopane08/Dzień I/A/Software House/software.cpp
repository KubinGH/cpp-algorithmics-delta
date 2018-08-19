#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1<<20;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint64_t A[MAX], B[MAX], T[MAX], S[MAX], M[MAX];
    static vector<uint32_t> C[MAX];
    for(uint32_t i = 1; i < n; i++)
        cin >> A[i], A[i]--, C[A[i]].push_back(i);
    for(uint32_t i = 1; i < n; i++)
        cin >> B[i];
    for(uint32_t i = n; i --> 0; )
    {
        T[i] = 1;
        S[i] = B[i];
        M[i] = -1llu;
        for(uint32_t v : C[i])
        {
            T[i] += T[v];
            S[i] += S[v];
            M[i] = min(M[i], min(M[v], B[v]));
        }
    }
    uint64_t r = 0;
    for(uint32_t u = 0; u < n; u++)
    {
        if(C[u].size() <= 1) continue;
        uint32_t mx = 0, mi = -1u;
        for(uint32_t v : C[u])
        {
            if(T[v] > mx)
                mx = T[v], mi = v;
        }
        if(2*mx > T[u] - 1)
        {
            uint64_t mp = -1llu;
            for(uint32_t v : C[u])
            {
                if(v != mi)
                    mp = min(mp, min(M[v], B[v]));
            }
            r += (2*mx - T[u] + 1) * mp;
        }
        else if(T[u] % 2 == 0)
            r += M[u];
        r += S[u] - B[u];
    }
    cout << r;
}
