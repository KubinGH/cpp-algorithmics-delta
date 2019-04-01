#include <bits/stdc++.h>

using namespace std;

struct Set
{
    priority_queue<uint64_t> S;
    uint64_t sum = 0;
    void push(uint64_t x) { S.push(x); sum += x; }
    void pop() { sum -= S.top(); S.pop(); }
    uint64_t top() { return S.top(); }
    bool empty() const { return S.empty(); }
    size_t size() const { return S.size(); }
};

uint32_t n, m;
vector<vector<uint32_t>> below;
vector<uint64_t> W, V;

pair<uint64_t, Set*> solve(uint32_t u)
{
    Set* S;
    uint64_t result = 0;
    S = new Set;
    S->push(W[u]);
    for(uint32_t v : below[u])
    {
        auto subv = solve(v);
        result = max(result, subv.first);
        auto Z = subv.second;
        if(S->size() < Z->size())
            swap(S, Z);
        while(not Z->empty())
            S->push(Z->top()), Z->pop();
        while(not S->empty() and S->sum > m)
            S->pop();
    }
    result = max(result, S->size() * V[u]);
    return {result, S};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    below.resize(n); W.resize(n); V.resize(n);
    for(uint32_t u = 0; u < n; u++)
    {
        uint32_t v;
        cin >> v >> W[u] >> V[u];
        if(u > 0)
            below[v-1].push_back(u);
    }
    cout << solve(0).first;
}
