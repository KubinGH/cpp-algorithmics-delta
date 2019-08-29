#include <bits/stdc++.h>

using namespace std;

int k;

map<vector<int>, int> cache;

int solve(vector<int> a)
{
    if(a.empty()) return 0;
    if(cache.count(a)) return cache[a];
    const size_t n = a.size();
    int result = INT_MAX / 3;
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = i+1; j <= n and a[i] == a[j-1]; j++)
        {
            auto b = a;
            b.erase(b.begin() + i, b.begin() + j);
            result = min(result, solve(b) + max(int(k - (j - i)), 0));
        }
    }
    return cache[a] = result;
}

int main()
{
    size_t n;
    cin >> n >> k;

    vector<int> a(n);
    for(size_t i = 0; i < n; i++)
        cin >> a[i];

    cout << solve(a);
}
