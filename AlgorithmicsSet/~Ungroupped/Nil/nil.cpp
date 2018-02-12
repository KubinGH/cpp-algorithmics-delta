#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint64_t, MAX> weights;
    for(uint32_t i = 0; i < n; i++)
        cin >> weights[i];
    static array<vector<uint32_t>, MAX> next;
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t before, after;
        cin >> before >> after; before--; after--;
        next[before].push_back(after);
    }
    stack<pair<uint32_t, uint64_t> > to_visit;
    to_visit.emplace(0, weights[0]);
    uint64_t best = 0;
    while(not to_visit.empty())
    {
        pair<uint32_t, uint64_t> current = to_visit.top();
        best = max(best, current.second);
        to_visit.pop();
        for(uint32_t n : next[current.first])
            to_visit.emplace(n, current.second + weights[n]);
    }
    cout << best;
}
