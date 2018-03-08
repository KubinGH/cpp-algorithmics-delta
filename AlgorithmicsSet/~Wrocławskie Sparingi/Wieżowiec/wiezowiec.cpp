#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t n;
    cin >> n;
    queue<pair<uint64_t, uint64_t>> Q;
    unordered_set<uint64_t> V;
    Q.emplace(0, 0);
    V.insert(0);
    while(not Q.empty())
    {
        uint64_t c = Q.front().first, d = Q.front().second; Q.pop();
        if(c == n)
        {
            cout << d;
            break;
        }
        if(V.find(c * 2) == V.end() and c * 2 <= n)
            Q.emplace(c * 2, d + 1), V.insert(c * 2);
        if(V.find(c - 1) == V.end())
            Q.emplace(c - 1, d + 1), V.insert(c - 1);
        if(V.find(c + 1) == V.end())
            Q.emplace(c + 1, d + 1), V.insert(c + 1);
    }
}
