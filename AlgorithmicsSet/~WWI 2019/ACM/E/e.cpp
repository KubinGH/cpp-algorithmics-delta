#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> poss = {
/*  3 */    {"000", "002", "003", "005", "100", "102", "103", "105", "300", "302", "303", "305"},
/*  6 */    {"000", "001", "005", "100", "105", "300", "305"},
/*  9 */    {"000", "001", "002", "003", "005", "100", "102", "103", "105", "300", "302", "303", "305"},
/* 12 */    {"000", "001", "002", "003", "005", "100", "102", "103", "105", "300", "302", "303", "305"},
/* 15 */    {"000", "001", "002", "003", "005", "100", "102", "103", "105", "300", "302", "303", "305"},
/* 18 */    {"000", "001", "002", "003", "005", "100", "102", "103", "105", "300", "302", "303", "305"}
};

map<pair<size_t, bool>, vector<string>> cache;

vector<string> generate(size_t n, bool lz)
{
    if(n == 0)
        return {""};
    else if(cache.count({n, lz}))
        return cache[{n, lz}];
    vector<string> rt;
    if(lz)
        for(auto s : generate(n - 1, lz))
            rt.push_back(s);
    for(auto x : poss[n - 1])
        for(auto s : generate(n - 1, false))
            rt.push_back(x + s);
    return cache[{n, lz}] = rt;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    auto S = generate(poss.size(), true);
    vector<uint64_t> N;
    for(auto s : S)
    {
        while(not s.empty() and s.front() == '0')
            s.erase(s.begin(), s.begin() + 1);
        if(s.empty()) continue;
        N.push_back(stoll(s));
    }
    N.push_back(1e18);
    sort(N.begin(), N.end());
    N.erase(unique(N.begin(), N.end()), N.end());

    size_t q;
    cin >> q;

    for(size_t i = 0; i < q; i++)
    {
        uint64_t a, b;
        cin >> a >> b;
        cout << upper_bound(N.begin(), N.end(), b) - lower_bound(N.begin(), N.end(), a) << '\n';
    }
}
