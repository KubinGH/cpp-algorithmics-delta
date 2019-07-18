#include <bits/stdc++.h>
#include <ktl/text/kmr.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    const size_t n = S.size();
    for(size_t i = 0; i < n; i++)
        S.push_back('$');

    karp_miller_rosenberg kmr(S.begin(), S.end());

    vector<pair<pair<size_t, size_t>, size_t>> keys(n);
    for(size_t i = 0; i < n; i++)
        keys[i] = {kmr(i, i + n), i};

    sort(keys.begin(), keys.end());

    for(auto p : keys)
        cout << p.second << '\n';
}
