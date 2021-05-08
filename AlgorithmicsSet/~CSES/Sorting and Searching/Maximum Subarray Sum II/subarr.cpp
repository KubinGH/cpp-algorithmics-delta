#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, a, b;
    cin >> n >> a >> b;

    vector<int> A(n);
    vector<int64_t> S(n + 1);
    for(size_t i = 0; i < n; i++)
        cin >> A[i], S[i+1] = S[i] + A[i];

    int64_t result = INT64_MIN;
    set<pair<int64_t, size_t>> vals;
    for(size_t i = a; i <= b; i++)
    {
        vals.emplace(S[i-a], i-a);
        result = max(result, S[i] - vals.begin()->first);
    }
    for(size_t i = b+1; i <= n; i++)
    {
        vals.erase({S[i-b-1], i-b-1});
        vals.emplace(S[i-a], i-a);
        result = max(result, S[i] - vals.begin()->first);
    }
    cout << result << endl;
}
