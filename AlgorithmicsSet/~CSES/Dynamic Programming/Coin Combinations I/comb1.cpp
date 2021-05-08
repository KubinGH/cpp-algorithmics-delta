#include <bits/stdc++.h>

using namespace std;

const uint64_t mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, x;
    cin >> n >> x;

    vector<size_t> C(n);
    for(auto& c : C)
        cin >> c;
    sort(C.begin(), C.end());

    vector<uint64_t> R(x+1);
    R[0] = 1;

    for(size_t a = 0; a <= x; a++)
    {
        for(auto c : C)
            if(a >= c)
                R[a] += R[a - c];
        R[a] %= mod;
    }

    cout << R[x] << endl;
}
