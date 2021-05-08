#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<pair<int, int>> T(n);
    for(auto& [a, d] : T)
        cin >> a >> d;

    sort(T.begin(), T.end());
    int64_t t = 0, r = 0;
    for(auto [a, d] : T)
        r += d - (t += a);

    cout << r << endl;
}
