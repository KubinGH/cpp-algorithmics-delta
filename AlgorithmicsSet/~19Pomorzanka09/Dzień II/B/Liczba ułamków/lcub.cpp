#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

template<typename Function>
auto harmonic_for(size_t n, size_t hi, Function f)
{
    int64_t result = 0;
    for(size_t i = 1, j; i <= hi; i = j + 1)
    {
        j = n / (n / i);
        result += f(i, min(j, hi));
    }
    return result;
}

int main()
{
    vector<int> Mu(MAX);
    Mu[1] = 1;
    for(size_t i = 1; i < MAX; i++)
        for(size_t x = 2*i; x < MAX; x += i)
            Mu[x] -= Mu[i];

    size_t T;
    cin >> T;
    while(T --> 0)
    {
        int n, m;
        cin >> n >> m;

        int64_t result = 0;
        for(int d = 1; d <= m; d++)
        {
            int64_t b = harmonic_for(n/d, m/d, [&](int i, int j) {
                return int64_t(j-i+1) * ((n/d)/i);
            });
            int64_t bb = b, r = harmonic_for(n/d, m/d, [&](int i, int j) {
                int64_t v = (n/d) / i, l = j-i+1;
                int64_t x = l * b - l*(l+1)/2 * v;
                b -= l*v;
                return x;
            });
            r *= 2; r += bb;

            result += r * Mu[d];
        }

        cout << result << endl;
    }
}
