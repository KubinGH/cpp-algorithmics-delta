#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    array<vector<size_t>, 3> state;
    for(size_t i = n; i --> 0; )
        state[0].push_back(i);

    vector<pair<size_t, size_t>> result;

    function<void(size_t, size_t)> fun = [&](size_t s, size_t t) {
        if(state[s].empty())
            return;
        else if(state[s].size() == 1)
        {
            result.emplace_back(s, t);
            state[t].push_back(state[s].back());
            state[s].pop_back();
        }
        else
        {
            const size_t f = (0 ^ 1 ^ 2) ^ (s ^ t), x = state[s].front();
            state[s].erase(state[s].begin());
            fun(s, f);
            result.emplace_back(s, t);
            fun(f, t);
            state[t].insert(state[t].begin(), x);
        }
    };

    fun(0, 2);

    cout << result.size() << endl;
    for(auto& [s, t] : result)
        cout << s+1 << ' ' << t+1 << '\n';
}
