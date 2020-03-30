#include <bits/stdc++.h>

using namespace std;
using uint = unsigned;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    uint cnt[64] = {};

    vector<uint64_t> B(n);
    for(auto& b : B)
    {
        cin >> b;
        cnt[__builtin_ctzll(b)]++;
    }

    int k = max_element(begin(cnt), end(cnt)) - cnt;

    cout << (n - cnt[k]) << endl;
    for(size_t i = 0; i < n; i++)
        if(__builtin_ctzll(B[i]) != k)
            cout << B[i] << ' ';
    cout << endl;
}
