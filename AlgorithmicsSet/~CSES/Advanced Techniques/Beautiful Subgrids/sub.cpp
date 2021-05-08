#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("popcnt,avx")

using namespace std;

const size_t N = 3030;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<bitset<N>> A(n);
    for(auto& b : A)
        cin >> b;

    uint64_t r = 0;
    auto f = [](uint64_t x) { return x*(x-1) / 2; };
    for(size_t i = 0; i < n; i++)
        #pragma GCC ivdep
        for(size_t j = i+1; j < n; j++)
            r += f((A[i] & A[j]).count());

    cout << r << endl;
}
