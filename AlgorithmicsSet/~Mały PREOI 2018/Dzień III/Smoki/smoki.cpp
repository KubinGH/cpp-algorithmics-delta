#include <bits/stdc++.h>

using namespace std;

template<typename Callable>
void for_each_neighbour(uint32_t w, uint32_t h, uint32_t x, uint32_t y, Callable callback)
{
    if(x+1 < w)
        callback(x+1, y);
    if(y+1 < h)
        callback(x, y+1);
    if(x > 0)
        callback(x-1, y);
    if(y > 0)
        callback(x, y-1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t h, w, t;
    cin >> h >> w >> t;
    queue<uint32_t> Q;
    vector<uint32_t> aflame_since(w*h, -1u);
    auto I = [&](uint32_t x, uint32_t y) {
        return y*w + x;
    };
    auto X = [&](uint32_t i) { return i % w; };
    auto Y = [&](uint32_t i) { return i / w; };
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
    {
        char c;
        cin >> c;
        if(c == 'x')
        {
            aflame_since[I(x, y)] = 0;
            Q.push(I(x, y));
        }
    }
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        if(aflame_since[u] > t)
            break;
        for_each_neighbour(w, h, X(u), Y(u), [&](uint32_t nx, uint32_t ny) {
            uint32_t v = I(nx, ny);
            if(aflame_since[v] == -1u)
            {
                aflame_since[v] = aflame_since[u] + 1;
                Q.push(v);
            }
        });
    }
    vector<pair<uint32_t, uint32_t>> result;
    for(uint32_t i = 0; i < w*h; i++)
        if(aflame_since[i] <= t)
            result.emplace_back(Y(i)+1, X(i)+1);
    sort(result.begin(), result.end());
    cout << result.size() << "\n";
    for(auto p : result)
        cout << p.first << " " << p.second << "\n";
}
