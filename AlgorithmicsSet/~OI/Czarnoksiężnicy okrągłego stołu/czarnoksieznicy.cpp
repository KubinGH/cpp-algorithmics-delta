#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 12, MAX_P = 3;
const uint32_t MOD = 1e9 + 7;

uint32_t abs_diff(uint32_t u, uint32_t v) { return u>v ? u - v : v - u; }

int main()
{
    uint32_t n, k, p;
    cin >> n >> k >> p;
    vector<bitset<2*MAX_P+1>> A(n);
    vector<bool> E(n); fill(E.begin(), E.end(), 1);
    for(uint32_t i = 0; i < n; i++)
        A[i].set();
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        if(abs_diff(u, v) <= p)
            A[u][p+u-v] = false;
        if(v == n-1)
            E[u] = false;
    }
    if(n <= 10)
    {
        vector<uint32_t> V(n);
        iota(V.begin()+1, V.end(), 0); V[0] = n-1;
        uint32_t r = 0;
        do {
            bool ok = true;
            for(uint32_t i = 0; i < n - 1; i++)
                if(abs_diff(V[i], V[i+1]) > p or not A[V[i]][p+V[i]-V[i+1]])
                    ok = false;
            if(abs_diff(V[0], V[n-1]) > p or not E[V[n-1]])
                ok = false;
            if(ok) r++;
        } while(next_permutation(V.begin()+1, V.end()));
        cout << r;
    }
    else if(p <= 1)
    {
        cout << 0;
    }
    else if(p == 2)
    {

    }
    else
    {

    }
}
