#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    if(n == 1)
    {
        cout << "01" << endl;
        return 0;
    }

    n--;
    vector<vector<size_t>> graph(1 << n);
    for(size_t i = 0; i < (1u << n); i++)
    {
        size_t u = i >> 1, v = u ^ (1u << (n - 1));
        graph[i].push_back(u);
        graph[i].push_back(v);
    }

    vector<size_t> tovis = {0}, circuit;
    while(not tovis.empty())
    {
        auto u = tovis.back();
        if(not graph[u].empty())
            tovis.push_back(graph[u].back()), graph[u].pop_back();
        else
            circuit.push_back(u), tovis.pop_back();
    }

    cout << string(n - 1, '0');
    for(auto u : circuit)
        cout << (u & 1);
    cout << endl;
}
