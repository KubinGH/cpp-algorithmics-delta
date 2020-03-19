#include <bits/stdc++.h>

using namespace std;

template<size_t N>
struct polyqueue
{
    size_t n = 0;
    queue<pair<uint, size_t>> Q[N];

    bool empty() { return not n; }

    size_t argmin() const
    {
        size_t t = SIZE_MAX;
        for(size_t i = 0; i < N; i++)
            if(not Q[i].empty() and (t == SIZE_MAX or Q[i].front().first < Q[t].front().first))
                t = i;
        return t;
    }
    const pair<uint, size_t>& front() const { return Q[argmin()].front(); }
    void pop() { n--; Q[argmin()].pop(); }
    void push(uint d, size_t v, uint w) { n++; Q[w].emplace(d + w, v); }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint x;
    cin >> x;

    polyqueue<10> Q;

    vector<uint> dist(x+1, UINT_MAX);
    vector<bool> lock(x+1);
    vector<pair<size_t, char>> back(x);

    Q.push(0, x, 0);
    while(not lock[0])
    {
        auto [d, v] = Q.front(); Q.pop();
        if(lock[v])
            continue;
        lock[v] = true;
        for(uint c = 0; c < 10; c++)
        {
            auto u = (v*10 + c) % x;
            if(dist[v] + c < dist[u])
            {
                dist[u] = dist[v] + c;
                Q.push(d, u, c);
                back[u] = {v, '0' + c};
            }
        }
    }

    string S;
    size_t v = 0;
    while(v != x)
        S += back[v].second, v = back[v].first;
    reverse(S.begin(), S.end());

    cout << S << endl;
}
