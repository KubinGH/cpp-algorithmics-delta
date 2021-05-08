#include <bits/stdc++.h>

using namespace std;

const size_t K = 6;
const int64_t mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int64_t a[K] = {1};
    for(size_t i = 0; i < K; i++)
        for(size_t j = 0; j < i; j++)
            a[i] += a[j];

    size_t n;
    cin >> n;
    while(n --> 0)
    {
        rotate(a, a + 1, a + K);
        a[K-1] = accumulate(a, a + K, 0l) % mod;
    }

    cout << a[0] << endl;
}
