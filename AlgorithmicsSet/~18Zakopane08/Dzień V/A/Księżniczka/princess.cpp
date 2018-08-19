#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 300, MAX2 = MAX * MAX;

mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b)
    { return uniform_int_distribution<T>{a, b}(gen); }

template<typename Callback>
void for_each_neighbour(uint32_t i, uint32_t w, uint32_t h, Callback callback)
{
    uint32_t x = i % w, y = i / w;
    if(x > 0) callback(x - 1, y);
    if(y > 0) callback(x, y - 1);
    if(x < w - 1) callback(x + 1, y);
    if(y < h - 1) callback(x, y + 1);
}

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t T = 0;
  cin >> T;
  while(T --> 0)
  {
    gen.seed(time(0) ^ 4201337);
    uint32_t h, w;
    cin >> h >> w;
    static bitset<MAX2> wet;
    for(uint32_t i = 0; i < w*h; i++)
    {
        char c;
        cin >> c;
        wet[i] = c == '.';
    }
    static bitset<MAX2> used, vis;
    uint32_t total_best = 0;
    vector<uint32_t> P; P.reserve(w*h);
    for(uint32_t i = 0; i < w*h; i++)
    {
        if(wet[i] and not vis[i])
        {
            queue<uint32_t> Q;
            Q.push(i); vis[i] = true;
            while(not Q.empty())
            {
                uint32_t u = Q.front(); Q.pop();
                P.push_back(u);
                for_each_neighbour(u, w, h,
                    [&](uint32_t x, uint32_t y) {
                        if(wet[y*w + x] and not vis[y*w + x])
                            vis[y*w + x] = true, Q.emplace(y*w + x);
                });
             }
            for(uint32_t i : P) vis[i] = false;
            uint32_t best = 0;
            static bitset<MAX2> tus;
            for(uint32_t t = 0; t < 128; t++)
            {
                uint32_t r = 0;
                queue<uint32_t> Q; Q.push(i);
                vis[i] = true;
                if(t == 0) tus[i] = 0;
                else if(t == 1) tus[i] = 1;
                else if(t >= 2) tus[i] = randint(0, 127) <= 80;
                r += tus[i];
                while(not Q.empty())
                {
                    uint32_t u = Q.front(); Q.pop();
                    bool anytus = false;
                    for_each_neighbour(u, w, h,
                        [&](uint32_t x, uint32_t y) {
                        uint32_t v = y*w + x;
                        if(tus[v])
                            anytus = true;
                    });
                    if(anytus)
                        r -= tus[u], tus[u] = false;
                    for_each_neighbour(u, w, h,
                        [&](uint32_t x, uint32_t y) {
                            uint32_t v = y*w + x;
                            if(wet[v] and not vis[v])
                            {
                                vis[v] = true;
                                tus[v] = tus[u] ? 0 : (t >= 2 ? randint(0, 127) <= 40 : 1);
                                r += tus[v];
                                Q.push(v);
                            }
                    });
                }
                for(uint32_t u : P)
                {
                    if(tus[u]) continue;
                    bool anytus = false;
                    for_each_neighbour(u, w, h,
                        [&](uint32_t x, uint32_t y) {
                        uint32_t v = y*w + x;
                        if(tus[v])
                            anytus = true;
                    });
                    if(not anytus)
                        tus[u] = true, r++;
                }
                if(best < r)
                {
                    for(uint32_t i : P) used[i] = tus[i];
                    best = r;
                }
                for(uint32_t i : P) tus[i] = false, vis[i] = false;
            }
            total_best += best;
            for(uint32_t i : P) vis[i] = true;
        }
        P.clear();
    }
    cout << total_best << "\n";
    for(uint32_t y = 0, i = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++, i++)
        {
            cout << (wet[i] and used[i] ? '.' : '#');
            wet[i] = vis[i] = used[i] = false;
        }
        cout << "\n";
    }
  }
}
