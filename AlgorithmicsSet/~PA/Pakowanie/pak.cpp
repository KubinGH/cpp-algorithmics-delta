#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const size_t nul = SIZE_MAX/2;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<int> A(n), C(m);
    for(auto& a : A) cin >> a;
    for(auto& c : C) cin >> c;

    sort(C.rbegin(), C.rend());
    C.push_back(0);

    vector<pair<size_t, int>> dist(1 << n, {nul, 0});
    dist[0] = {0, 0};

    for(size_t u = 0; u < (1u << n); u++)
    {
        auto [x, c] = dist[u];
        for(size_t i = 0; i < n; i++)
          if(not (u >> i & 1))
        {
            const size_t v = u | (1 << i);
            pair<size_t, int> d0 = {x, c + A[i]}, d1 = {x+1, A[i]};
            if(c + A[i] <= C[x] and d0 < dist[v])
                dist[v] = d0;
            else if(A[i] <= C[x+1] and d1 < dist[v])
                dist[v] = d1;
        }
    }

    if(dist[(1<<n)-1].first == nul)
        cout << "NIE" << endl;
    else
        cout << dist[(1<<n)-1].first + (dist[(1<<n)-1].second > 0) << endl;
}
