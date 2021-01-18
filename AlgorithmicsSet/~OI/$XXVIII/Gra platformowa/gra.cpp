// Jakub Bachurski
// Gra platformowa - O((n + h) log n)

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <climits>
#include <vector>
#include <deque>
#include <array>

using namespace std;

const uint32_t nul = UINT32_MAX;

template<typename T, size_t N>
struct static_vector
{
    size_t n;
    array<T, N> arr;

    static_vector() : n(0) {}
    T& operator[] (size_t i) { return arr[i]; }
    const T& operator[] (size_t i) const { return arr[i]; }

    void push_back(const T& v) { arr[n++] = v; }
    void pop_back() { n--; }

    typename array<T, N>::iterator begin() { return arr.begin(); }
    typename array<T, N>::iterator end() { return arr.begin() + n; }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q; int w;
    cin >> n >> w >> q;

    vector<vector<int>> ids(n);
    vector<size_t> cnt_till(n+1);

    auto id = [&](uint32_t y, int x) {
        auto it = lower_bound(ids[y].begin(), ids[y].end(), x);
        return cnt_till[y] + (it - ids[y].begin());
    };

    vector<vector<int>> holes(n);
    for(size_t y = 0; y < n; y++)
    {
        size_t k;
        cin >> k;
        holes[y].resize(k);
        ids[y].reserve(ids[y].size() + 2*k + 5);
        for(auto& x : holes[y])
        {
            cin >> x; x--;
            ids[y].push_back(x-1); ids[y].push_back(x+1);
            if(y+1 < n) ids[y+1].push_back(x);
        }
        ids[y].push_back(0); ids[y].push_back(w-1);
    }
    for(size_t y = 0; y < n; y++)
    {
        sort(ids[y].begin(), ids[y].end());
        ids[y].erase(unique(ids[y].begin(), ids[y].end()), ids[y].end());
        cnt_till[y+1] = cnt_till[y] + ids[y].size();
    }
    const size_t m = cnt_till[n];

    vector<static_vector<uint32_t, 3>> graph(m);
    deque<uint32_t> que;

    for(size_t y = 0; y < n; y++)
    {
        for(size_t j = 0; j < ids[y].size(); j++)
        {
            auto x = ids[y][j]; auto i = cnt_till[y] + j;
            if(x == w-1) { que.push_back(i); continue; }
            const uint32_t r = cnt_till[y] + (j + 1);
            if(binary_search(holes[y].begin(), holes[y].end(), x + 1))
            {
                graph[r].push_back(2*i + 1);
                if(y+1 < n)
                {
                    const size_t p = id(y + 1, x + 1);
                    graph[p].push_back(2*i + 0);
                    graph[r].push_back(2*p + 1);
                }
            }
            else
                graph[r].push_back(2*i + 0);
        }
    }

    vector<uint32_t> dist(m, nul);
    for(auto u : que) dist[u] = 0;

    while(not que.empty())
    {
        auto u = que.front(); que.pop_front();
        for(auto vg : graph[u])
        {
            size_t v = vg >> 1, g = vg & 1;
            if(dist[u] + g < dist[v])
            {
                if(g) que.push_back(v);
                else  que.push_front(v);
                dist[v] = dist[u] + g;
            }
        }
    }

    while(q --> 0)
    {
        size_t y;
        cin >> y; y--;
        cout << dist[id(y, 0)] << '\n';
    }
}
