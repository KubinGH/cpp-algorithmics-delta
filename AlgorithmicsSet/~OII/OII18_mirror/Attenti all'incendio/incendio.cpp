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

template<size_t N>
struct disjoint_set
{
    array<size_t, N> parent, nrank;
    disjoint_set(size_t init = N)
    {
        iota(parent.begin(), parent.begin() + init, 0);
    }
    void unite(size_t first_node, size_t second_node)
    {
        size_t first = find_root(first_node),
               second = find_root(second_node);
        if(nrank[second] > nrank[first])
        {
            parent[first] = second;
            nrank[second]++;
        }
        else
        {
            parent[second] = first;
            if(nrank[first] == nrank[second])
                nrank[first]++;
        }
    }
    size_t find_root(size_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
};

int alzati(int N, int M, int X[], int Y[])
{
    uint32_t n = N, m = M;
    uint32_t *A = (uint32_t*)X, *B = (uint32_t*)Y;
    if(m == 1)
        return min({max(A[0], B[0]), max(((n-1) - A[0]), ((n-1) - B[0])), n})-1;
    set<uint32_t> SX, SY;
    for(uint32_t i = 0; i < m; i++)
        SX.insert(A[i]), SY.insert(B[i]);
    if(SX.size() == 1)
    {
        auto it = SY.end(); it--;
        return min({max(A[0], *SY.begin()), max((n-1) - A[0], (n-1) - *it), n})-1;
    }
    static disjoint_set<1<<22> dset(n*n);
    static bitset<1<<22> V;
    static uint32_t P[1<<22];
    static vector<pair<uint32_t, uint32_t>> O[1<<16];
    queue<pair<uint32_t, uint32_t>> Q;
    for(uint32_t i = 0; i < m; i++)
    {
        Q.emplace(A[i], B[i]);
        V[B[i]*n+A[i]] = true;
        O[0].emplace_back(A[i], B[i]);
    }
    while(not Q.empty())
    {
        auto u = Q.front(); Q.pop();
        for_each_neighbour(u.first, u.second, n, n,
            [&](uint32_t x, uint32_t y) {
                if(not V[y*n+x])
                {
                    Q.emplace(x, y);
                    V[y*n+x] = true;
                    P[y*n+x] = P[u.second*n+u.first] + 1;
                    O[P[y*n+x]].emplace_back(x, y);
                }
        });
    }
    for(uint32_t p = (1<<16); p --> 0;)
    {
        for(auto c : O[p])
        {
            uint32_t x, y; tie(x, y) = c;
            for_each_neighbour(x, y, n, n,
                [&](uint32_t cx, uint32_t cy) {
                    if(P[cy*n+cx] >= p)
                        dset.unite(y*n+x, cy*n+cx);
            });
        }
        if(dset.find_root(0) == dset.find_root((n-1)*n + (n-1)))
            return p - 1;
    }
    return -1;
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
