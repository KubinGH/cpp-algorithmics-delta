#include <bits/stdc++.h>
#define shandom_ruffle shuffle

using namespace std;

const size_t TRIES = 128;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;

    vector<pair<size_t, size_t>> edges;
    edges.reserve(m);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        if(--u > --v)
            swap(u, v);
        edges.emplace_back(u, v);
    }
    sort(edges.begin(), edges.end());
    vector<size_t> run(n + 1);
    iota(run.begin(), run.begin() + n, 0);

    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    for(size_t t = 0; t < TRIES; t++)
    {
        shandom_ruffle(run.begin(), run.begin() + n, gen);
        run[n] = run[0];
        bool ok = true;
        for(size_t i = 0; i < m and ok; i++)
        {
            size_t u = run[i], v = run[i+1];
            if(u > v)
                swap(u, v);
            if(binary_search(edges.begin(), edges.end(), make_pair(u, v)))
                ok = false;
        }
        if(ok)
        {
            cerr << endl;
            for(size_t i = 0; i < m; i++)
                cout << run[i]+1 << " " << run[i+1]+1 << "\n";
            return 0;
        }
    }
    cout << -1;

}
