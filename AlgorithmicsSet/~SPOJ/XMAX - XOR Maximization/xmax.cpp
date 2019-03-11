#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;

    vector<uint64_t> basis;

    auto push_vec = [&](uint64_t a) {
        for(uint64_t b : basis)
            a = min(a, a ^ b);
        if(a)
            basis.push_back(a);
    };

    for(uint32_t i = 0; i < n; i++)
        push_vec([&](){ uint64_t a; cin >> a; return a; }());

    sort(basis.rbegin(), basis.rend());
    uint64_t r = 0;
    for(uint64_t b : basis)
        if(not (r & (1llu << __lg(b))))
            r ^= b;
    cout << r;
}
