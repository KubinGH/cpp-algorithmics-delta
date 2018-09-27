#include <bits/stdc++.h>

using namespace std;

template<typename T, typename CallbackType>
void for_each_neighbour(T x, T y, T w, T h, CallbackType callback)
{
    if(x > 0)       callback(x - 1, y);
    if(y > 0)       callback(x, y - 1);
    if(x < w - 1)   callback(x + 1, y);
    if(y < h - 1)   callback(x, y + 1);
}
uint32_t dist(uint32_t a, uint32_t b) { return a>b ? a - b : b - a; }

int alzati(int N, int M, int X[], int Y[])
{
    uint32_t n = N, m = M;
    uint32_t *A = (uint32_t*)X, *B = (uint32_t*)Y;
    uint32_t lo = 0, hi = 4*n;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        queue<pair<uint32_t, uint32_t>> Q;
        set<pair<uint32_t, uint32_t>> V;
        Q.emplace(0, 0); V.emplace(0, 0);
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for_each_neighbour(u.first, u.second, n, n,
                [&](uint32_t x, uint32_t y) {
                    if(V.find({x, y}) != V.end()) return;
                    bool ok = true;
                    for(uint32_t i = 0; i < m and ok; i++)
                    {
                        if(dist(x, A[i]) + dist(y, B[i]) <= mid)
                            ok = false;
                    }
                    if(ok) Q.emplace(x, y), V.emplace(x, y);
            });
        }
        if(V.find({n-1, n-1}) != V.end())
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo - 1;
}

#ifdef XHOVA
int main()
{
    int n, m;
    cin >> n >> m;
    static int X[1<<14], Y[1<<14];
    for(int i = 0; i < m; i++)
        cin >> X[i] >> Y[i];
    cout << alzati(n, m, X, Y);
}
#endif // XHOVA
