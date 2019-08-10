#include <bits/stdc++.h>
#include "pol.h"

using namespace std;

int main()
{
    size_t n = LiczbaWierzcholkow(), m = LiczbaKrawedzi();

    vector<uint64_t> edge_cost(m);
    vector<size_t> choice(n, SIZE_MAX);

    for(size_t i = 0; i < m; i++)
    {
        int u, v; long long w;
        NastepnaKrawedz(&u, &v, &w);
        edge_cost[i] = w;

        if(u == v)
            continue;

        auto up = [&](size_t c) {
            if(choice[c] == SIZE_MAX or (uint64_t)w < edge_cost[choice[c]])
                choice[c] = i;
        };
        up(u); up(v);
    }

    vector<bool> used(m);
    for(size_t i = 0; i < n; i++)
        if(choice[i] != SIZE_MAX and not used[choice[i]])
            WybierzKrawedz(choice[i]), used[choice[i]] = true;

    Zakoncz();
}
