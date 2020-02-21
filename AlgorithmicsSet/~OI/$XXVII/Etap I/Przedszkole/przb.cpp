#include <iostream>
#include <vector>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    while(q --> 0)
    {
        size_t k;
        cin >> k;

        size_t pos = power(k, n);
        vector<size_t> col(n);
        size_t ret = 0;
        for(size_t mask = 0; mask < pos; mask++)
        {
            size_t maskie = mask;
            for(size_t i = 0; i < n; i++, maskie /= k)
                col[i] = maskie % k;
            bool ok = true;
            for(size_t u = 0; u < n; u++)
                for(size_t v : graph[u])
                    if(col[u] == col[v])
                        ok = false;
            ret += ok;
        }
        cout << ret << endl;
    }
}
