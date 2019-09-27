#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<pair<size_t, size_t>> basic;
    set<pair<size_t, size_t>> all;
    for(size_t i = 0; i < m; i++)
    {
        size_t x, y;
        cin >> x >> y;
        basic.emplace_back(x, y);
        all.emplace(x, y);
    }

    bool done = false;
    while(not done)
    {
        done = true;
        auto call = all;
        for(auto p : call)
            for(auto q : call)
                if(p.second == q.first and not all.count({q.second, p.first}))
                    all.emplace(q.second, p.first), done = false;
    }

    cout << all.size();
}
