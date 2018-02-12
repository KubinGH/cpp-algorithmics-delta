#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<uint32_t, MAX> height;
    uint32_t max_height = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> height[i];
        if(height[i] > max_height)
            max_height = height[i];
    }
    if(max_height == height[0])
    {
        cout << height[0];
        return 0;
    }
    static array<vector<uint32_t>, MAX> graph;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    queue<uint32_t> Q;
    static array<uint32_t, MAX> H;
    fill(H.begin(), H.begin() + n, numeric_limits<uint32_t>::max());
    Q.push(0);
    H[0] = height[0];
    while(not Q.empty())
    {
        uint32_t c = Q.front(); Q.pop();
        if(c < n - 1) for(uint32_t next : graph[c])
        {
            if(max(H[c], height[next]) < H[next])
            {
                H[next] = max(H[c], height[next]);
                Q.push(next);
            }
        }
        else continue;
    }
    cout << H[n-1];
}
