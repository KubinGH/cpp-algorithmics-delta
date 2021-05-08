#include <bits/stdc++.h>

using namespace std;

namespace std
{
    template<>
    struct hash<array<char, 9>>
    {
        size_t operator() (const array<char, 9>& arr) const
        {
            size_t h = 0;
            for(size_t i = 0; i < 9; i++)
                h *= 31, h += arr[i];
            return h;
        }
    };
}

int main()
{
    vector<array<char, 9>> perm;
    array<char, 9> fin = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    do {
        perm.push_back(fin);
    } while(next_permutation(fin.begin(), fin.end()));

    unordered_map<array<char, 9>, size_t> id;
    id.reserve(1 << 21);
    for(size_t i = 0; i < perm.size(); i++)
        id[perm[i]] = i;

    vector<size_t> dist(perm.size(), SIZE_MAX);
    queue<array<char, 9>> que;
    auto maybe = [&](const array<char, 9>& v, size_t d) {
        auto i = id[v];
        if(dist[i] == SIZE_MAX)
            dist[i] = d, que.push(v);
    };

    maybe(fin, 0);
    while(not que.empty())
    {
        auto u = que.front(); que.pop();
        auto d = dist[id[u]];
        for(size_t y = 0; y < 3; y++)
            for(size_t x = 0; x < 2; x++)
                swap(u[3*y+x], u[3*y+x+1]), maybe(u, d+1), swap(u[3*y+x], u[3*y+x+1]);
        for(size_t x = 0; x < 3; x++)
            for(size_t y = 0; y < 2; y++)
                swap(u[3*y+x], u[3*y+x+3]), maybe(u, d+1), swap(u[3*y+x], u[3*y+x+3]);
    }

    array<char, 9> st;
    for(auto& x : st)
        cin >> x;
    cout << dist[id[st]] << endl;
}
