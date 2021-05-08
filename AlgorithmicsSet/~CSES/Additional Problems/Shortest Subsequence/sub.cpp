#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    const size_t n = S.size();
    auto ch = [&](size_t i) {
        switch(S[i])
        {
            case 'A': return 0;
            case 'C': return 1;
            case 'T': return 2;
            case 'G': return 3;
        }
        return 4;
    };
    auto no = [&](size_t i) {
        constexpr const char* p = "ACTG";
        return p[i];
    };

    array<vector<size_t>, 4> occ;
    for(size_t i = 0; i < n; i++)
        occ[ch(i)].push_back(i);
    for(size_t c = 0; c < 4; c++)
        occ[c].push_back(n);

    auto edge = [&](size_t i, size_t c) {
        return *lower_bound(occ[c].begin(), occ[c].end(), i) + 1;
    };

    vector<pair<size_t, size_t>> path(n+2, {SIZE_MAX, 4});
    path.back() = {0, 4};
    for(size_t i = n+1; i --> 0; )
    {
        for(size_t c = 0; c < 4; c++)
            path[i] = min(path[i], make_pair(path[edge(i, c)].first + 1, c));
        // cout << i << ": " << path[i].first << " #" << no(path[i].second) << " -> " << edge(i, path[i].second) << endl;
    }

    string R;
    size_t curr = 0;
    while(curr <= n)
        R.push_back(no(path[curr].second)), curr = edge(curr, path[curr].second);

    cout << R << endl;
}
