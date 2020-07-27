#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <complex>
#include <algorithm>

using namespace std;

vector<vector<pair<size_t, int>>> graph;
vector<complex<int>> val;
vector<bool> vis;
vector<size_t> ord;
double force_x; bool forcing_x;

void fail()
{
    cout << "NO" << endl;
    exit(0);
}

void dfs(size_t u)
{
    vis[u] = true;
    ord.push_back(u);
    for(auto [v, c] : graph[u])
    {
        if(not vis[v])
            val[v] = c - val[u], dfs(v);
        else
        {
            auto y = c - val[u] - val[v];
            if(y != 0)
            {
                if(not y.imag()) fail();
                auto x = -1.0 * y.real() / y.imag();
                if(forcing_x and abs(x - force_x) > 1e-7) fail();
                forcing_x = true;
                force_x = x;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph.resize(n); val.resize(n); vis.resize(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int c;
        cin >> u >> v >> c; u--; v--;

        graph[u].emplace_back(v, c);
        graph[v].emplace_back(u, c);
    }

    cout << fixed << setprecision(7);

    vector<double> ret(n);
    for(size_t s = 0; s < n; s++)
      if(not vis[s])
    {
        val[s] = {0, 1};

        ord.clear();
        forcing_x = false;
        dfs(s);

        double x = force_x;
        if(not forcing_x)
        {
            vector<int> v;
            v.reserve(ord.size());
            for(size_t u : ord)
                v.push_back((val[u].imag() < 0 ? 1 : -1) * val[u].real());
            nth_element(v.begin(), v.begin() + v.size()/2, v.end());
            x = v[v.size()/2];
        }

        for(size_t u : ord)
            ret[u] = val[u].real() + val[u].imag()*x;
    }

    cout << "YES" << endl;
    for(size_t u = 0; u < n; u++)
        cout << ret[u] << ' ';
    cout << endl;
}
