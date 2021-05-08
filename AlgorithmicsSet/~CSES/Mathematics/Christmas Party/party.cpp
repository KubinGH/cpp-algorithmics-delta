#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9 + 7;
constexpr size_t MAX = 1 << 20;

int main()
{
    static uint derangements[MAX];
    derangements[0] = 1; derangements[2] = 1;

    for(size_t n = 3; n < MAX; n++)
        derangements[n] = (n - 1) * (derangements[n - 1] + derangements[n - 2]) % mod;

    uint n;
    cin >> n;
    cout << derangements[n] << endl;
}
