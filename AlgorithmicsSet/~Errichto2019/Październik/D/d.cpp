#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> anti(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        anti[u].push_back(v);
        anti[v].push_back(u);
    }

    for(size_t u = 0; u < n; u++)
        sort(anti[u].begin(), anti[u].end());

    vector<bool> isvis(n);
    vector<size_t> unvis(n);
    iota(unvis.begin(), unvis.end(), 0);

    vector<size_t> components;

    for(size_t s = 0; s < n; s++)
    {
        if(isvis[s])
            continue;

        size_t cnt = 0;

        isvis[s] = true;
        unvis.erase(find(unvis.begin(), unvis.end(), s));

        stack<size_t> tovis; tovis.push(s);
        while(not tovis.empty())
        {
            size_t u = tovis.top(); tovis.pop();
            cnt++;

            vector<size_t> newvis, rest;
            set_difference  (unvis.begin(), unvis.end(), anti[u].begin(), anti[u].end(), back_inserter(newvis));
            set_intersection(unvis.begin(), unvis.end(), anti[u].begin(), anti[u].end(), back_inserter(rest));
            for(auto v : newvis)
                isvis[v] = true, tovis.push(v);
            swap(unvis, rest);
        }

        components.push_back(cnt);
    }

    sort(components.begin(), components.end());
    cout << components.size() << endl;
    for(auto x : components)
        cout << x << " ";
}
