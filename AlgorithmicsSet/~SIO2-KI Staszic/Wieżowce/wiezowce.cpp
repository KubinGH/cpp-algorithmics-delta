#include <bits/stdc++.h>

using namespace std;

template<typename T>
T next() { T x; cin >> x; return x; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> H, M;
    H.reserve(1<<21); M.reserve(1<<21);
    auto push = [&](uint32_t h) {
        if(h >= H[M.back()])
            M.push_back(H.size());
        else
            M.push_back(M.back());
        H.push_back(h);
    };
    auto pop = [&]() {
        H.pop_back(); M.pop_back();
    };
    H.push_back(0); M.push_back(0);
    for(uint32_t i = 0; i < n; i++)
        push(next<uint32_t>());
    cout << M.back()-1 << "\n";
    uint32_t q;
    cin >> q;
    while(q --> 0)
    {
        uint32_t t;
        cin >> t;
        if(t == 1)
            push(next<uint32_t>());
        else if(t == 2)
            pop();
        cout << M.back()-1 << "\n";
    }
}
