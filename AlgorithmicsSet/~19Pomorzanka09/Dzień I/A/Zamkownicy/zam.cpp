#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const size_t MAX = 1 << 16;

template<typename T>
vector<T> unique_elements(vector<T> e)
{
    sort(e.begin(), e.end());
    e.erase(unique(e.begin(), e.end()), e.end());
    return e;
}

template<typename T>
void minimize(T& var, T val)
{
    if(val < var)
        var = val;
}


size_t popcount(size_t mask)
{
    return __builtin_popcount(mask);
}

struct bdata { size_t root_on, root_off; };


size_t rel[MAX];


bdata Building(size_t root = SIZE_MAX, size_t depth = 0)
{
    size_t n, m, w;
    cin >> n >> m >> w;

    vector<pair<size_t, size_t>> edges;
    vector<size_t> inner; inner.reserve(2 * m);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;

        edges.emplace_back(u, v);
        inner.push_back(u); inner.push_back(v);
    }
    inner = unique_elements(inner);
    if(root == SIZE_MAX) root = inner.front();
    iter_swap(inner.begin(), find(inner.begin(), inner.end(), root));

    for(size_t i = 0; i < n; i++)
        rel[inner[i]] = i;

    vector<pair<size_t, bdata>> below;
    below.reserve(w);

    for(size_t i = 0; i < w; i++)
    {
        size_t u, b;
        cin >> u >> b;
        below.emplace_back(rel[u], Building(b, depth + 1));
    }

    vector<vector<size_t>> igraph(n);
    vector<size_t> ngraph(n);

    for(auto e : edges)
    {
        igraph[rel[e.first ]].push_back(rel[e.second]);
        igraph[rel[e.second]].push_back(rel[e.first ]);
        ngraph[rel[e.first ]] |= (1 << rel[e.second]);
        ngraph[rel[e.second]] |= (1 << rel[e.first ]);
    }

    bdata result = {SIZE_MAX, SIZE_MAX};

    for(size_t mask = 0; mask < (1u << n); mask++)
    {
        vector<size_t> covered(n);
        for(size_t u = 0; u < n; u++)
            if(mask>>u & 1)
                for(auto v : igraph[u])
                    covered[u] |= (1 << v), covered[v] |= (1 << u);

        if(covered != ngraph)
            continue;

        auto pop = popcount(mask);

        for(auto p : below)
        {
            if(mask>>p.first & 1)
                pop += min(p.second.root_on, p.second.root_off);
            else
                pop += p.second.root_on;
        }

        if(mask & 1)
        {
            minimize(result.root_on, pop);
            minimize(result.root_off, pop);
        }
        else
            minimize(result.root_off, pop);
    }

    return result;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;

    while(T --> 0)
    {
        auto result = Building();
        cout << min(result.root_on, result.root_off) << endl;
    }
}
