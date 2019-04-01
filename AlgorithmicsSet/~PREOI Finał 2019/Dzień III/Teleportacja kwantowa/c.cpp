#include <bits/stdc++.h>

using namespace std;

template<typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

uint32_t adiff(uint32_t a, uint32_t b) { return a > b ? a - b : b - a; }

int main()
{
    uint32_t H, W, n;
    cin >> H >> W >> n;

    vector<uint32_t> Y(n), X(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> Y[i] >> X[i];

    vector<bool> done(n);
    vector<uint32_t> opt(n, -1u);
    vector<uint32_t> track(n, -1u);

    track[0] = -1u; opt[0] = 0;

    min_queue<pair<uint32_t, uint32_t>> Q;
    Q.push({0, 0});

    while(not Q.empty())
    {
        uint32_t u = Q.top().second; Q.pop();
        if(done[u]) continue;
        done[u] = true;
        //cerr << "@ " << u+1 <<  " (" << opt[u] << ")" << endl;
        for(uint32_t v = 0; v < n; v++) if(not done[v])
        {
            uint32_t w = max(adiff(X[u], X[v]), adiff(Y[u], Y[v]));
            if(opt[u] + (1u << w) < opt[v])
            {
                opt[v] = opt[u] + (1u << w);
                track[v] = u;
                //cerr << "push " << v+1 << " with priority " << w << endl;
                Q.push({opt[v], v});
            }
        }
    }

    stack<uint32_t> result;
    uint32_t u = n-1;
    while(u != -1u)
    {
        result.push(u);
        u = track[u];
    }
    cout << result.size() << "\n";
    while(not result.empty())
        cout << result.top()+1 << " ", result.pop();
}
