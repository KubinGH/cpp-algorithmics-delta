#include <bits/stdc++.h>

int dajN(); int dajK(); int dajM(); int nastepna(); void zwieksz(); void koniec();

using namespace std;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n = dajN(), k = dajK();

    vector<uint> malus(n+1, k);
    vector<vector<size_t>> graph(n+1);
    for(size_t d = 1; d <= k; d++)
        for(size_t i = 0; i + d <= n; i += d)
            graph[i + d].push_back(i), malus[i]--;

    vector<size_t> less_deg(n+1);
    vector<double> e(n+1, numeric_limits<double>::infinity()), less_e(n+1);

    auto E = [&](size_t u) {
        return (less_e[u] + graph[u].size() + malus[u]) / less_deg[u];
    };

    min_priority_queue<pair<double, size_t>> Q;
    vector<bool> lock(n+1);

    Q.emplace(0, n);
    while(not Q.empty())
    {
        size_t u = Q.top().second; Q.pop();

        if(lock[u]) continue;
        lock[u] = true;
        e[u] = less_deg[u] ? E(u) : 0;

        for(auto v : graph[u]) if(not lock[v])
        {
            less_e[v] += e[u];
            less_deg[v]++;
            Q.emplace(E(v), v);
        }
    }

    cerr << "ev: " << e[0] << endl;

    mt19937 gen(1337);
    for(size_t t = 0; t < 100; t++)
    {
        int c = 0; size_t i = 0;
        while(c < (int)n)
        {
            auto x = nastepna();
            if(c + x <= (int)n and c % x == 0 and e[c + x] <= e[c]+gen()%2)
                c += x, zwieksz();
            i++;
        }
        cerr << i << endl;
        koniec();
    }
}
