#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<uint> A(n);

    for(auto& x : A) cin >> x;

    vector<uint> G(n);
    for(size_t u = 0; u < n; u++)
        G[u] |= (1 << u);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        G[u] |= (1 << v);
        G[v] |= (1 << u);
    }

    uint result = 0;
    vector<size_t> clique;
    for(uint z = 0; z < (1u << n); z++)
    {
        uint g = (1 << n) - 1;
        for(size_t i = 0; i < n; i++)
            if(z >> i & 1)
                g &= G[i];
        if((z & g) == z)
        {
            uint r = 0;
            vector<size_t> c;
            for(size_t i = 0; i < n; i++)
                if(z >> i & 1)
                    r += A[i], c.push_back(i);
            if(r > result)
                result = r, clique = c;
        }
    }

    cout << result << '\n' << clique.size() << '\n';
    for(auto u : clique)
        cout << u+1 << ' ';
}
